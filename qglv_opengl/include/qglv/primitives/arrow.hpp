/**
 * @file include/qglv/primitives/arrow.hpp
 */
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef qglv_opengl_ARROW_HPP_
#define qglv_opengl_ARROW_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <sophus/se3.hpp>

#include "../gl/headers.hpp"
#include "../gl/helpers.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qglv {

/*****************************************************************************
** Interfaces
*****************************************************************************/

/**
 * The arrow part of the code here comes from libqglviewer.h. We could use QGLViewer::drawArrow() directly, but this
 * removes a dependency on it. To apply a colour, call glColour first:
 *
 * @code
 * glColour(gl::Blue);
 * arrow(pose, length, radius);
 * @endcode
 */
template<typename T>
void arrow( const Sophus::SE3Group<T> & pose, const float &length, const float &radius = 1.0 )
{
  static const int subdivisions = 12;
  static GLUquadric* quadric = gluNewQuadric();

  glPushMatrix();
  const Eigen::Matrix<T,3,1> & center = pose.translation();
  qglv::translate(center);
  Eigen::Matrix<T,3,1> axis_angle = pose.so3().log();
  double angle = axis_angle.norm();
  if(angle != 0.)
  {
    glRotatef(angle*180.0/M_PI,  // radians to degrees
               axis_angle[0],
               axis_angle[1],
               axis_angle[2]);
  }
  // cylinder below points in the z direction, but we want it in the x direction, so rotate accordingly
  glRotatef(90.0f, 0.0, 1.0, 0.0);
  float used_radius = radius;
  if (radius < 0.0) {
    used_radius = 0.05 * length;
  }
  const double head = 2.5*(used_radius / length) + 0.1;
  const double coneRadiusCoef = 4.0 - 5.0 * head;
  gluCylinder(quadric, used_radius, used_radius, length * (1.0 - head/coneRadiusCoef), subdivisions, 1);
  glTranslatef(0.0f, 0.0f, float(length * (1.0 - head)));
  gluCylinder(quadric, coneRadiusCoef * used_radius, 0.0, head * length, subdivisions, 1);
//  glTranslatef(float(-length * (1.0 - head)), 0.0f, 0.0f);
  glPopMatrix();
}

/*****************************************************************************
** Trailers
*****************************************************************************/

} // namespace qglv

#endif /* qglv_opengl_ARROW_HPP_ */
