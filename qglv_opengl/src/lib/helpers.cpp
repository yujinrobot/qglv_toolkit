/**
 * @file /qglv/src/lib/gl/helpers.cpp
 * 
 * @brief Short description of this file.
 **/
/*****************************************************************************
 ** Includes
 *****************************************************************************/

#include "../../include/qglv/gl/headers.hpp"
#include "../../include/qglv/gl/helpers.hpp"

/*****************************************************************************
 ** Namespaces
 *****************************************************************************/

namespace qglv {

/*****************************************************************************
 ** Implementation
 *****************************************************************************/

void moveTo(const Sophus::SE3f& T)
{
  Sophus::SE3f pose = T.inverse();
  const Eigen::Vector3f & center = pose.translation();
  translate(center);
  Eigen::Vector3f axis_angle = pose.so3().log();
  double angle = axis_angle.norm();
  if (angle != 0.)
  {
    glRotatef(angle * 180.0 / M_PI,
              static_cast<float>(axis_angle[0]),
              static_cast<float>(axis_angle[1]),
              static_cast<float>(axis_angle[2])
              );
  }
}

void seeWhatISee(const Sophus::SE3f& pose, const unsigned int& image_width, const unsigned int& image_height,
                 const float &focal_length)
{
  // https://www.opengl.org/archives/resources/faq/technical/viewing.htm

  float aspect_ratio(static_cast<float>(image_width) / static_cast<float>(image_height));
  float fovy = ::atan2f(static_cast<float>(image_height) * 0.5f, focal_length) * 180.0f / M_PI * 2.0f;

  glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective
  glLoadIdentity();
  gluPerspective(fovy, aspect_ratio, 0.1, 10000.0); // angle fov, aspect ratio, nearz, farz

  glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
  glLoadIdentity();

  float distance = 10.0;
  Eigen::Vector3f up;
  up << 0, 1, 0;
  Eigen::Vector3f tmp_eye = pose.translation();
  Eigen::Vector3f tmp_look = tmp_eye + pose.so3() * Eigen::Vector3f(0, 0, distance);
  Eigen::Vector3f tup = pose.so3() * up;
  gluLookAt(tmp_eye.x(), tmp_eye.y(), tmp_eye.z(), tmp_look.x(), tmp_look.y(), tmp_look.z(), tup.x(), tup.y(), tup.z());
}

} // namespace qglv
