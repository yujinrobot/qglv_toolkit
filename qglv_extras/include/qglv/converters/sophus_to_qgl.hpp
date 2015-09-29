/**
 * @file include/qglv/sophus2qgl.hpp
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef qglv_extensions_SOPHUS_HPP_
#define qglv_extensions_SOPHUS_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QGLViewer/frame.h>
#include <sophus/se3.hpp>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qglv {

/**
 * Convert a sophus pose to a qglviewer frame.
 */
qglviewer::Frame sophusPose2QGLFrame(const Sophus::SE3f& pose);

/**
 * Get the translational part of a sophus pose as a qglviewer Vec.
 * @param pose
 * @return
 */
qglviewer::Vec sophusPose2QGLTranslation(const Sophus::SE3f& pose);

qglviewer::Quaternion sophusPose2QGLOrientation(const Sophus::SE3f& pose);

} // namespace qglv

#endif /* qglv_extensions_SOPHUS_HPP_ */
