/**
 * @file /src/lib/keyframes.cpp
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <qglv/opengl.hpp>
#include "../../include/qglv/gl/colours.hpp"
#include "../../include/qglv/gl/helpers.hpp"
#include "../../include/qglv/objects/keyframes.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qglv {

/*****************************************************************************
 ** Static Variables
 *****************************************************************************/

const float KeyFrame::default_keyframe_size = 0.3;

/*****************************************************************************
 ** Construct without cloud
 *****************************************************************************/

KeyFrame::KeyFrame(const int id,
                   const Sophus::SE3f& T_frame_rel_map,
                   const AxisColourScheme& axis_colour_scheme,
                   const float& axis_scale_factor
                   )
: id(id)
, T_frame_rel_map(T_frame_rel_map)
, updated(true)
, gl_id_start(-1)
, pinned(false)
, axis_colour_scheme(axis_colour_scheme)
, axis_scale_factor(axis_scale_factor)
{
}

/*****************************************************************************
** Construct from a Tracking Frame
*****************************************************************************/

KeyFrame::KeyFrame(
         const Sophus::SE3f& T,
         const std::vector<Eigen::Vector3f>& seeds,
         const std::vector<float>& seed_variances,
         const std::vector<unsigned char>& seed_intensities
        )
: id(-1)
, T_frame_rel_map(T)
, updated(true)
, gl_id_start(-1)
, pinned(false)
, axis_colour_scheme(AxisColourGolden)
, axis_scale_factor(1.25)
{
  // not very optimal...better to reserve and then push back
  vertices.resize( seeds.size() * 3 );
  variance_lines.resize( seeds.size() * 3 * 2 );

  // precompute some data for the point clouds
  float * ptr_vertices = vertices.data();
  float * ptr_var = variance_lines.data();
  Eigen::Vector3f lm0, lmp, lmn;

  for( int j(0); j < seeds.size(); j++ )
  {
    float r, g, b;
    normalisedValueToRGB(static_cast<float>(seed_intensities[j])/255.0f, b, g, r); // make sure to convert away from char

    intensities.push_back(255*r);
    intensities.push_back(255*g);
    intensities.push_back(255*b);

    lm0.x() = seeds[j].x();
    lm0.y() = seeds[j].y();
    lm0.z() = seeds[j].z();

    *ptr_vertices++ = lm0.x();
    *ptr_vertices++ = lm0.y();
    *ptr_vertices++ = lm0.z();

    float depth = lm0.z();
    lm0 /= depth;

    // draw the variance as line
    float depth_n = depth + seed_variances[j];
    float depth_p = depth - seed_variances[j];
    if( depth_p < 1e-3f ) depth_p = 1e-3f;
    lmp = lm0 * depth_p;
    lmn = lm0 * depth_n;

    *ptr_var++ = lmp.x();
    *ptr_var++ = lmp.y();
    *ptr_var++ = lmp.z();

    *ptr_var++ = lmn.x();
    *ptr_var++ = lmn.y();
    *ptr_var++ = lmn.z();
  }
}

/*****************************************************************************
 ** Construct from a Mapped Keyframe
 *****************************************************************************/

KeyFrame::KeyFrame(const int id,
         const Sophus::SE3f& T,
         const bool& pinned,
         const std::vector<Eigen::Vector3f>& seeds,
         const std::vector<float>& seed_variances,
         const std::vector<unsigned char>& seed_intensities,
         const float& focal_length_times_baseline
        )
: id(id)
, T_frame_rel_map(T)
, pinned(pinned)
, updated(true)
, gl_id_start(-1)
{
  axis_colour_scheme = pinned ? AxisColourGolden : AxisColourRGB;
  axis_scale_factor = pinned ? 1.25 : 1.0;

  // not very optimal...better to reserve and then push back
  vertices.reserve( seeds.size() * 3 );
  variance_lines.reserve( seeds.size() * 3 * 2 );

  // precompute some data for the point clouds
  float * ptr_var = variance_lines.data();
  Eigen::Vector3f lm0, lmp, lmn;
//  const float depth_variance_threshold = 0.04f;
  const float depth_variance_threshold = 0.02f;
  const float sq_depth_variance_threshold = depth_variance_threshold *depth_variance_threshold;

  for( int j(0); j < seeds.size(); j++ )
  {
//    float disp_var = std::sqrt( seed_variances[j] );
//    float disp = focal_length_times_baseline / seeds[j].z();
//    float disp_f = (disp - disp_var); if( disp_f < 1e-3f ) disp_f = 1e-3f;
//    float disp_n = (disp + disp_var);
//    float depth_var = focal_length_times_baseline / disp_f - focal_length_times_baseline / disp_n;
    
    float inverse_depth_var = std::sqrt( seed_variances[j] );
    float inverse_depth = 1.0f / seeds[j].z();
    float inverse_depth_f = (inverse_depth - inverse_depth_var); if( inverse_depth_f < 1e-3f ) inverse_depth_f = 1e-3f;
    float inverse_depth_n = (inverse_depth + inverse_depth_var);
    float depth_var = 1.0f / inverse_depth_f - 1.0f / inverse_depth_n;
    
    depth_var *= depth_var;

    if( depth_var < sq_depth_variance_threshold) {
      intensities.push_back( seed_intensities[j] );
      intensities.push_back( seed_intensities[j] );
      intensities.push_back( seed_intensities[j] );

      lm0.x() = seeds[j].x();
      lm0.y() = seeds[j].y();
      lm0.z() = seeds[j].z();

      vertices.push_back(seeds[j].x());
      vertices.push_back(seeds[j].y());
      vertices.push_back(seeds[j].z());

      float depth = lm0.z();
      lm0 /= depth;

      // draw the variance as line
      float depth_n = depth + 0.0;
      float depth_p = depth - 0.0;
      if( depth_p < 1e-3f ) depth_p = 1e-3f;
      lmp = lm0 * depth_p;
      lmn = lm0 * depth_n;

      variance_lines.push_back(lmp.x());
      variance_lines.push_back(lmp.y());
      variance_lines.push_back(lmp.z());

      variance_lines.push_back(lmn.x());
      variance_lines.push_back(lmn.y());
      variance_lines.push_back(lmn.z());
    }
  }
}

KeyFrame::~KeyFrame() {
  if ( gl_id_start > 0 ) {
    glDeleteLists(gl_id_start, 3);
  }
}

void KeyFrame::draw(
    bool draw_frames,
    bool draw_seeds,
    bool draw_covariances
    )
{
  if (gl_id_start == -1) {
    _glGenLists();
  }
  GLfloat model[16];
  glPushMatrix();
  qglv::moveTo(T_frame_rel_map);
  if ( draw_frames ) { glCallList(gl_id_start); }
  if ( draw_seeds )  { glCallList(gl_id_start + 1); }
  if ( draw_covariances ) { glCallList(gl_id_start + 2); }
  glPopMatrix();
}

void KeyFrame::_glGenLists() {
  gl_id_start = ::glGenLists(3);

  glNewList( gl_id_start, GL_COMPILE );
  // pose
  // note the identity SE3f() here, we're just drawing in place
  pose(Sophus::SE3f(),
                 axis_scale_factor*default_keyframe_size,
                 axis_scale_factor*2.0,
                 axis_colour_scheme
                 );
  if ( !name.empty() ) {
    // TODO : figure out how to render the text locally relative to the frame
    // refer to renderText and QGLViewer.drawText
  }
  glEndList();

  glNewList( gl_id_start + 1, GL_COMPILE );
  if ( vertices.size() > 0 ) {
    // point cloud
    glPointSize(1);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices.data() );
    glColorPointer(3, GL_UNSIGNED_BYTE, 0, intensities.data() );
    glDrawArrays(GL_POINTS, 0, vertices.size() / 3 );
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
  }
  glEndList();
  glNewList( gl_id_start + 2, GL_COMPILE );
  if ( variance_lines.size() > 0 ) {
    glColor4f(0.0f, 0.5f, 0.0f, 0.5f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, variance_lines.data() );
    glDrawArrays(GL_LINES, 0, variance_lines.size() / 3 );
    glDisableClientState(GL_VERTEX_ARRAY);
  }
  glEndList();
}

} // namespace qglv
