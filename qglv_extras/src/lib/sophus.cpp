/**
 * @file /qglv/src/lib/gl/sophus2qgl.cpp
 * 
 * @brief Short description of this file.
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <Eigen/Core>
#include <sophus/se3.hpp>

#include "../../include/qglv/converters/sophus_to_qgl.hpp"


/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qglv {

qglviewer::Frame sophusPose2QGLFrame(const Sophus::SE3f& pose) {
  return qglviewer::Frame(sophusPose2QGLTranslation(pose),
                          sophusPose2QGLOrientation(pose));
}

qglviewer::Vec sophusPose2QGLTranslation(const Sophus::SE3f& pose) {
  qglviewer::Vec translation(pose.translation().x(),
                             pose.translation().y(),
                             pose.translation().z()
                            );
  return translation;
}


qglviewer::Quaternion sophusPose2QGLOrientation(const Sophus::SE3f& pose) {
  Eigen::Vector3f axis_angle = pose.so3().log();
  double angle = axis_angle.norm();
  qglviewer::Vec axis(axis_angle[0],
                      axis_angle[1],
                      axis_angle[2]
                     );
  return qglviewer::Quaternion(axis, angle);
}

} // namespace qglv
