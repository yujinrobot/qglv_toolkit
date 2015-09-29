/**
 * @file src/lib/gl_draw_3d.cpp
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include <qglv/opengl.hpp>

#include "../../include/qglv/primitives/qgl_pose.hpp"
#include "../../include/qglv/objects/camera.hpp"

/*****************************************************************************
** Namespace
*****************************************************************************/

namespace qglv {

/*****************************************************************************
 ** Drawing methods
 *****************************************************************************/

Camera::Camera(const float& width, const float& height,
               const float& u0,
               const float& v0,
               const float& focal_length_in_pixels,
               const Sophus::SE3f& pose
               )
  : width(width),
    height(height),
    principal_point(u0, v0),
    focal_length(focal_length_in_pixels),
    pose(pose)
{
  // for the texture mapping
  const float arb_distance = 500.0f;
  float l, r, t, b;
  l = -arb_distance * principal_point.x() / focal_length;
  t = -arb_distance * principal_point.y() / focal_length;
  r =  arb_distance * (static_cast<float>(width)-principal_point.x()) / focal_length;
  b =  arb_distance * (static_cast<float>(height)-principal_point.y()) / focal_length;
  frustum[0] = Eigen::Vector3f(l,t,arb_distance);
  frustum[1] = Eigen::Vector3f(r,t,arb_distance);
  frustum[2] = Eigen::Vector3f(r,b,arb_distance);
  frustum[3] = Eigen::Vector3f(l,b,arb_distance);
}

/**
 * Convert the tracker calculated T_cam_rel_map transform into a
 * camera pose.
 *
 * Refer to our transform cheat sheets on transforms <-> poses
 *    https://docs.google.com/a/yujinrobot.com/document/d/1HRgc0avn08vL_LGN8-SuiaaSQUYt4HbBwwZtVOGzMIo/edit#
 *
 * @param T_cam_rel_map
 */
void Camera::setPose(const Sophus::SE3f& T_cam_rel_map) {
  pose = T_cam_rel_map.inverse();
  for ( unsigned int i = 0; i < 4; ++i ) {
    updated_frustum[i] = pose*frustum[i];
  }
}


void Camera::draw() {
  // pose - push/pop inside
  poseQGLStyle(pose, 1.0);

  // frustrum
  glPushMatrix();

  glColor4f(0.3f, 0.0f, 1.0f, 0.5f);
  Eigen::Vector3f fpoint[4];
  for( int i(0); i<4; i++ )
  {
    fpoint[i] = pose * (frustum[i] / 500.0f);
    line( pose.translation(), fpoint[i] );
  }

  line( fpoint[0], fpoint[1] );
  line( fpoint[1], fpoint[2] );
  line( fpoint[2], fpoint[3] );
  line( fpoint[3], fpoint[0] );

  glColor4f(1.0f,0.0f,0.0f, 0.5f); point( fpoint[0], 2.0f );
  glColor4f(0.0f,1.0f,0.0f, 0.5f); point( fpoint[1], 2.0f );
  glColor4f(0.0f,0.0f,1.0f, 0.5f); point( fpoint[2], 2.0f );

  glPopMatrix();
}

} // namespace qglv

