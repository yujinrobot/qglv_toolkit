/**
 * @file include/qglv/primitives/pose.hpp
 */
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef qglv_opengl_POSE_HPP_
#define qglv_opengl_POSE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <sophus/se3.hpp>
#include "../gl/headers.hpp"
#include "../gl/colours.hpp"
#include "../gl/helpers.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qglv {

/*****************************************************************************
** Interfaces
*****************************************************************************/

template<typename T>
void pose( const Sophus::SE3Group<T> & pose, const float &size, const float &width = 1.0, const AxisColourScheme colour_scheme = AxisColourRGB )
{
  glPushMatrix();
  const Eigen::Matrix<T,3,1> & center = pose.translation();

  qglv::translate(center);

  Eigen::Matrix<T,3,1> axis_angle = pose.so3().log();
  double angle = axis_angle.norm();
  if(angle != 0.)
  {
    glRotatef(angle * 180.0 / M_PI,
               axis_angle[0], axis_angle[1], axis_angle[2]);
  }

  float cached_line_width;
  glGetFloatv(GL_LINE_WIDTH, &cached_line_width);
  glLineWidth(width);
  switch (colour_scheme) {
    case AxisColourWhite:
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);  line(Eigen::Vector3f(0,0,0), Eigen::Vector3f(size, 0, 0));
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);  line(Eigen::Vector3f(0,0,0), Eigen::Vector3f(0, size, 0));
      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);  line(Eigen::Vector3f(0,0,0), Eigen::Vector3f(0, 0, size));
      break;
    case AxisColourGray:
      glColor4f(0.6f, 0.6f, 0.6f, 1.0f);  line(Eigen::Vector3f(0,0,0), Eigen::Vector3f(size, 0, 0));
      glColor4f(0.4f, 0.4f, 0.4f, 1.0f);  line(Eigen::Vector3f(0,0,0), Eigen::Vector3f(0, size, 0));
      glColor4f(0.2f, 0.2f, 0.2f, 1.0f);  line(Eigen::Vector3f(0,0,0), Eigen::Vector3f(0, 0, size));
      break;
    case AxisColourFadedBlue:
      glColor4f(0.9f, 0.9f, 1.0f, 1.0f);  line(Eigen::Vector3f(0,0,0), Eigen::Vector3f(size, 0, 0));
      glColor4f(0.7f, 0.7f, 1.0f, 1.0f);  line(Eigen::Vector3f(0,0,0), Eigen::Vector3f(0, size, 0));
      glColor4f(0.4f, 0.4f, 1.0f, 1.0f);  line(Eigen::Vector3f(0,0,0), Eigen::Vector3f(0, 0, size));
      break;
    case AxisColourGolden:
      glColor4f(1.0f, 0.8f, 0.0f, 1.0f);  line(Eigen::Vector3f(0,0,0), Eigen::Vector3f(size, 0, 0));
      glColor4f(0.6f, 0.4f, 0.1f, 1.0f);  line(Eigen::Vector3f(0,0,0), Eigen::Vector3f(0, size, 0));
      glColor4f(0.5f, 0.3f, 0.0f, 1.0f);  line(Eigen::Vector3f(0,0,0), Eigen::Vector3f(0, 0, size));
      break;
    case AxisColourGreen:
      glColor4f(0.0f, 1.0f, 0.0f, 1.0f);  line(Eigen::Vector3f(0,0,0), Eigen::Vector3f(size, 0, 0));
      glColor4f(0.0f, 0.7f, 0.0f, 1.0f);  line(Eigen::Vector3f(0,0,0), Eigen::Vector3f(0, size, 0));
      glColor4f(0.0f, 0.4f, 0.0f, 1.0f);  line(Eigen::Vector3f(0,0,0), Eigen::Vector3f(0, 0, size));
      break;
    case AxisColourBlue:
      glColor4f(0.0f, 0.0f, 1.0f, 1.0f);  line(Eigen::Vector3f(0,0,0), Eigen::Vector3f(size, 0, 0));
      glColor4f(0.0f, 0.0f, 0.7f, 1.0f);  line(Eigen::Vector3f(0,0,0), Eigen::Vector3f(0, size, 0));
      glColor4f(0.0f, 0.0f, 0.4f, 1.0f);  line(Eigen::Vector3f(0,0,0), Eigen::Vector3f(0, 0, size));
      break;
    case AxisColourRed:
      glColor4f(1.0f, 0.0f, 0.0f, 1.0f);  line(Eigen::Vector3f(0,0,0), Eigen::Vector3f(size, 0, 0));
      glColor4f(0.7f, 0.0f, 0.0f, 1.0f);  line(Eigen::Vector3f(0,0,0), Eigen::Vector3f(0, size, 0));
      glColor4f(0.4f, 0.0f, 0.0f, 1.0f);  line(Eigen::Vector3f(0,0,0), Eigen::Vector3f(0, 0, size));
      break;
    case AxisColourMagenta:
      glColor4f(1.0f, 0.0f, 1.0f, 1.0f);  line(Eigen::Vector3f(0,0,0), Eigen::Vector3f(size, 0, 0));
      glColor4f(0.8f, 0.0f, 0.8f, 1.0f);  line(Eigen::Vector3f(0,0,0), Eigen::Vector3f(0, size, 0));
      glColor4f(0.4f, 0.0f, 0.4f, 1.0f);  line(Eigen::Vector3f(0,0,0), Eigen::Vector3f(0, 0, size));
      break;
    default : // AxisColourRGB
      glColor3f(1.0f, 0.0f, 0.0f);  line(Eigen::Vector3f(0,0,0), Eigen::Vector3f(size, 0, 0));
      glColor3f(0.0f, 1.0f, 0.0f);  line(Eigen::Vector3f(0,0,0), Eigen::Vector3f(0, size, 0));
      glColor3f(0.0f, 0.0f, 1.0f);  line(Eigen::Vector3f(0,0,0), Eigen::Vector3f(0, 0, size));
      break;
  }
  glLineWidth(cached_line_width);
  glPopMatrix();
}

/*****************************************************************************
** Trailers
*****************************************************************************/

} // namespace qglv

#endif /* qglv_opengl_POSE_HPP_ */
