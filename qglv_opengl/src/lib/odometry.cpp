/**
 * @file /src/lib/odometry.cpp
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <cmath> // M_PI

#include "../../include/qglv/gl/headers.hpp"
#include "../../include/qglv/gl/colours.hpp"
#include "../../include/qglv/gl/helpers.hpp"
#include "../../include/qglv/primitives/arrow.hpp"
#include "../../include/qglv/objects/odometry.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qglv {

/*****************************************************************************
 ** Odometry
 *****************************************************************************/

Odometry::Odometry(const Sophus::SE3f& T_cam_rel_base)
: gl_id_global(-1)
, gl_id_window(-1)
, need_to_rebuild_global_list(false)
, need_to_rebuild_window_list(false)
, size_of_odometry_trail(25)
{
  T_extrinsics_rotation = Sophus::SE3f(T_cam_rel_base.rotationMatrix(), T_cam_rel_base.translation());
}

Odometry::~Odometry() {
  if ( gl_id_global > 0 ) {
    glDeleteLists(gl_id_global, 1);
  }
  if ( gl_id_window > 0 ) {
    glDeleteLists(gl_id_window, 1);
  }
}

void Odometry::update(const Sophus::SE3f& T_cam_rel_odom) {
  /********************
   ** All Odometry List
   ********************/
  static const float rotation_constraint = 18.0f * M_PI / 180.0;  // degrees to radians
  static const float squared_translation_constraint = 0.5*0.5;
  // check if we push a frame on the global
  Sophus::SE3f T_current = T_extrinsics_rotation.inverse()*T_cam_rel_odom;
  Sophus::SE3f pose_current = T_current.inverse();
  if ( global.size() == 0 ) {
    global.push_back(pose_current);
    need_to_rebuild_global_list = true;
  } else {
    Sophus::SE3f pose_last = global.back();
    Sophus::SE3f T_last = global.back().inverse();
    Sophus::SE3f T_difference = T_current * T_last.inverse();
    float squared_translation_difference = T_difference.translation().squaredNorm();
    float angle_difference_radians = T_last.unit_quaternion().angularDistance(T_current.unit_quaternion());
    if ( ( squared_translation_difference > squared_translation_constraint ) ||
         (angle_difference_radians > rotation_constraint ) ) {
//        std::cout << "*Differences: " << squared_translation_difference << "," << angle_difference_radians << "[" << rotation_constraint << "]" << std::endl;
      need_to_rebuild_global_list = true;
      global.push_back(pose_current);
    }
  }

  /********************
   ** Odometry Trail
   ********************/
  // Unrotate the camera rel odom transform so that it aligns with the robot front
  Sophus::SE3f T = T_extrinsics_rotation.inverse()*T_cam_rel_odom;
  window.push_back(T.inverse());
  if ( window.size() > size_of_odometry_trail ) {
    window.pop_front();
    need_to_rebuild_window_list = true;
  }
}

void Odometry::_glGenLists() {
  static const float draw_keyframe_size = 0.1;
  static const float draw_arrow_length = 0.3;
  static const float draw_arrow_radius = 0.01;

  if ( need_to_rebuild_window_list ) {
    if ( gl_id_window > 0 ) {
      glDeleteLists(gl_id_window, 1);
    }
    gl_id_window = ::glGenLists(1);
    glNewList( gl_id_window, GL_COMPILE );
    for ( const auto& pose : window ) {
      arrow(pose, 0.3*draw_arrow_length, 0.5*draw_arrow_radius);
    }
    glEndList();
  }

  if ( need_to_rebuild_global_list ) {
    if ( gl_id_global > 0 ) {
      glDeleteLists(gl_id_global, 1);
    }
    gl_id_global = ::glGenLists(1);
    glNewList( gl_id_global, GL_COMPILE );
    for ( const auto& pose : global ) {
      arrow(pose, draw_arrow_length, draw_arrow_radius);
    }
    glEndList();
  }
}

void Odometry::draw() {
  if ( need_to_rebuild_global_list || need_to_rebuild_window_list ) {
    _glGenLists();
    need_to_rebuild_global_list = false;
    need_to_rebuild_window_list = false;
  }
  qglv::colour(Magenta);
  glPushMatrix();
  if (gl_id_global > 0) {
    glCallList(gl_id_global);
  }
  if (gl_id_window > 0) {
    glCallList(gl_id_window);
  }
  glPopMatrix();
}

void Odometry::draw(const Sophus::SE3f& T_map_rel_odom) {
  if ( need_to_rebuild_global_list || need_to_rebuild_window_list ) {
    _glGenLists();
    need_to_rebuild_global_list = false;
    need_to_rebuild_window_list = false;
  }

  qglv::colour(Orange);
  glPushMatrix();
  qglv::moveTo(T_map_rel_odom.inverse());
  if (gl_id_global > 0) {
    glCallList(gl_id_global);
  }
  if (gl_id_window > 0) {
    glCallList(gl_id_window);
  }
  glPopMatrix();
}

/*****************************************************************************
 ** Trailers
 *****************************************************************************/

} // namespace qglv
