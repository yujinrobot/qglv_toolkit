/**
 * @file include/qglv/opencv.hpp
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef qglv_PCL_HPP_
#define qglv_PCL_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <memory>
#include <pcl/PCLPointCloud2.h>
#include <qglv/opengl.hpp>
#include <sophus/se3.hpp>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qglv {

/*****************************************************************************
** Factories
*****************************************************************************/

KeyFrame createKeyFrameFromPointCloud(
    const Sophus::SE3f& T_depth_rel_map,
    const std::shared_ptr<pcl::PCLPointCloud2>& point_cloud
    );

KeyFramePtr createKeyFramePtrFromPointCloud(
    const Sophus::SE3f& T_depth_rel_map,
    const std::shared_ptr<pcl::PCLPointCloud2>& point_cloud
    );

/**
 * @brief Implementation of the createKeyFrameFromPointCloud methods.
 */
void _initKeyFrameFromPointCloud(
    KeyFrame& keyframe,
    const Sophus::SE3f& T_depth_rel_map,
    const std::shared_ptr<pcl::PCLPointCloud2>& point_cloud
    );

} // namespace qglv

#endif /* qglv_PCL_HPP_ */
