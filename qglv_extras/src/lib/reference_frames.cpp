/**
 * @file /src/lib/reference_frames.cpp
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <qglv/opengl.hpp>
#include <QGLViewer/qglviewer.h>
#include <sophus/se3.hpp>
#include <string>
#include "../../include/qglv/objects/reference_frames.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qglv {
//
/*****************************************************************************
 ** Static Variables
 *****************************************************************************/

const float ReferenceFrame::default_keyframe_size = 0.6;

/*****************************************************************************
** Implementation
*****************************************************************************/

ReferenceFrame::ReferenceFrame(
         const std::string& name,
         const Sophus::SE3f& T,
         const Colour& colour,
         const Sophus::SE3f& parent
        )
: name(name)
, T_frame_rel_map(T)
, colour(colour)
, gl_id_start(-1)
{
}

ReferenceFrame::~ReferenceFrame() {
  if ( gl_id_start > 0 ) {
    glDeleteLists(gl_id_start, 1);
  }
}

void ReferenceFrame::draw()
{
  if (gl_id_start == -1) {
    _glGenLists();
  }
  GLfloat model[16];
  glPushMatrix();
  qglv::moveTo(T_frame_rel_map);
  glCallList(gl_id_start);
  glPopMatrix();
}

void ReferenceFrame::_glGenLists() {
  gl_id_start = ::glGenLists(1);
  glNewList( gl_id_start, GL_COMPILE );
  // pose
  QGLViewer::drawAxis(default_keyframe_size);
  qglv::moveTo(T_frame_rel_map.inverse());
  qglv::colour(colour);
  line(Eigen::Vector3f::Zero(), T_frame_rel_map.inverse().translation());
  // TODO : draw the text
  glEndList();
}

} // namespace qglv
