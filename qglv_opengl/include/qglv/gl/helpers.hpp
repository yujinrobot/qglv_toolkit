/**
 * @file include/qglv/gl/helpers.hpp
 **/
/*****************************************************************************
 ** Ifdefs
 *****************************************************************************/

#ifndef qglv_GL_HELPERS_HPP_
#define qglv_GL_HELPERS_HPP_

/*****************************************************************************
 ** Includes
 *****************************************************************************/

#include <Eigen/Core>
#include <sophus/se3.hpp>

#include "../gl/headers.hpp"

/*****************************************************************************
 ** Namespaces
 *****************************************************************************/

namespace qglv {

/*****************************************************************************
 ** Interfaces
 *****************************************************************************/

template<typename T>
inline void translate(const Eigen::Matrix<T, 3, 1> & v)
{
  glTranslatef(v[0], v[1], v[2]);
}

/**
 * Calls the appropriate glTranslatef and glRotatef for a given
 * sophus transform.
 */
void moveTo(const Sophus::SE3f& T);

/**
 * @brief Configure a gl viewport to see what a camera sees.
 *
 * This makes the gluPerspective, gluLookat calls appropriate for configuring
 * a camera's point of view.
 *
 * It does the fovy, aspect ratio calculations underneath given the simpler
 * camera/image parameters.
 *
 * https://www.opengl.org/archives/resources/faq/technical/viewing.htm
 */
void seeWhatISee(const Sophus::SE3f& pose, const unsigned int& image_width, const unsigned int& image_height,
                 const float &focal_length);

} // namespace qglv

#endif /* qglv_GL_HELPERS_HPP_ */
