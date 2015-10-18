/**
 * @file src/lib/gl_draw_3d.cpp
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include <qglv/opengl.hpp>
#include <QGLViewer/qglviewer.h>
#include <sophus/se3.hpp>

#include "../../include/qglv/converters/sophus_to_qgl.hpp"
#include "../../include/qglv/primitives/qgl_pose.hpp"

/*****************************************************************************
** Namespace
*****************************************************************************/

namespace qglv {

/*****************************************************************************
 ** Drawing methods
 *****************************************************************************/

/**
 * Makes use of QGL to draw a frame for the pose. Adds arrows and axis x-y-z text
 * beyond that of the draw:pose function.
 */
void poseQGLStyle(const Sophus::SE3f &pose, float size) {
  glPushMatrix();
  glMultMatrixd(sophusPose2QGLFrame(pose).matrix());
  QGLViewer::drawAxis(size);
  glPopMatrix();
}

} // namespace qglv

