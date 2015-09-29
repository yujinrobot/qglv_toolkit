/**
 * @file dinclude/qglv/primitives/geometry.hpp
 */
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef qglv_opengl_GEOMETRY_HPP_
#define qglv_opengl_GEOMETRY_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <Eigen/Core>
#include <vector>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qglv {

/*****************************************************************************
** Interfaces
*****************************************************************************/


void line( const Eigen::Vector3f & p1, const Eigen::Vector3f & p2);
void point( const Eigen::Vector3f & p, const float size = 1.0f );
void points( const std::vector< Eigen::Vector3f, Eigen::aligned_allocator<Eigen::Vector3f> > & p, const float size = 1.0f );
void vertex(const Eigen::Vector3f& p);

/**
 * The square is pinned with its lower left corner attached to the origin of
 * the current opengl frame and is aligned with the x-y plane of that frame.
 *
 * @param width
 * @param height
 */
void square(const float &width, const float& height);

/*****************************************************************************
** Trailers
*****************************************************************************/

} // namespace qglv

#endif /* qglv_opengl_GEOMETRY_HPP_ */
