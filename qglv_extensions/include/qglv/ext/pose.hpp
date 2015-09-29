/**
 * @file include/qglv/ext/pose.hpp
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef qglv_extensions_POSE_HPP_
#define qglv_extensions_POSE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <sophus/se3.hpp>

/*****************************************************************************
** Namespace
*****************************************************************************/

namespace qglv {
namespace ext {

void poseQGLStyle(const Sophus::SE3f &pose, float size=1.0f);

} // namespace ext
} // namespace qglv

#endif /* qglv_extensions_POSE_HPP_ */
