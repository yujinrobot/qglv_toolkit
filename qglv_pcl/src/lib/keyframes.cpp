/**
 * @file /src/lib/keyframes.cpp
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include "../../include/qglv/pcl.hpp"
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/common/projection_matrix.h>
#include <pcl/impl/point_types.hpp>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qglv {

/*****************************************************************************
** Implementation
*****************************************************************************/

KeyFrame createKeyFrameFromPointCloud(
    const Sophus::SE3f& T_depth_rel_map,
    const std::shared_ptr<pcl::PCLPointCloud2>& point_cloud
    )
{
  KeyFrame keyframe;
  _initKeyFrameFromPointCloud(keyframe, T_depth_rel_map, point_cloud);
  return keyframe;
}

KeyFramePtr createKeyFramePtrFromPointCloud(
    const Sophus::SE3f& T_depth_rel_map,
    const std::shared_ptr<pcl::PCLPointCloud2>& point_cloud
    )
{
  KeyFramePtr keyframe_ptr = std::make_shared<qglv::KeyFrame>();
  _initKeyFrameFromPointCloud(*keyframe_ptr, T_depth_rel_map, point_cloud);
  return keyframe_ptr;
}

void _initKeyFrameFromPointCloud(
    KeyFrame& keyframe,
    const Sophus::SE3f& T_depth_rel_map,
    const std::shared_ptr<pcl::PCLPointCloud2>& point_cloud
    )
{
  keyframe.T_frame_rel_map = T_depth_rel_map;
  keyframe.updated = true;
  // keyframe.gl_id_start = -1;
  keyframe.pinned = false;
  keyframe.axis_colour_scheme = AxisColourBlue;
  keyframe.axis_scale_factor = 0.5;

  std::shared_ptr<pcl::PointCloud<pcl::PointXYZ>> cloud(new pcl::PointCloud<pcl::PointXYZ>);
  pcl::fromPCLPointCloud2(*point_cloud, *cloud);
  keyframe.vertices.resize( cloud->size()*3 );
  keyframe.intensities.resize( cloud->size()*3 );
  float max_depth;
  for ( unsigned int i = 0; i < cloud->points.size(); ++i ) {
    keyframe.vertices[3*i] = cloud->points[i].x;
    keyframe.vertices[3*i+1] = cloud->points[i].y;
    keyframe.vertices[3*i+2] = cloud->points[i].z;
    max_depth = ( max_depth < cloud->points[i].z ) ? cloud->points[i].z : max_depth;
  }
  for ( unsigned int i = 0; i < cloud->points.size(); ++i ) {
    float r, g, b;
    normalisedValueToRGB((cloud->points[i].z/max_depth), r, g, b); // make sure to convert away from char
    keyframe.intensities[3*i] = 255*r;
    keyframe.intensities[3*i+1] = 255*g;
    keyframe.intensities[3*i+2] = 255*b;
  }
}

} // namespace qglv
