/**
 * @file include/qglv/objects/camera.hpp
 */
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef qglv_objects_CAMERA_HPP_
#define qglv_objects_CAMERA_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <Eigen/Core>
#include <memory>
#include <sophus/se3.hpp>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qglv {

/*****************************************************************************
** Interfaces
*****************************************************************************/


class Camera {
public:
  /**
   * @brief Construct a virtual camera from typical parameters.
   *
   * If from a dslam parameters file, this is usually the rectified
   * versions of width, height, u0 and v0.
   *
   * @code
   * Camera(parameters.rect_width, parameters.rect_height,
   *        parameters.rect_u0, parameters.rect_v0,
   *        parameters.focal_length_in_pixels,
   *        parameters.Te.inverse()
   *        )
   * @endcode
   *
   * @param width
   * @param height
   * @param u0
   * @param v0
   * @param focal_length_in_pixels
   * @param pose : initialise with the pose for the camera extrinsics
   */
  Camera(const float& width, const float& height,
         const float& u0, const float& v0,
         const float& focal_length_in_pixels,
         const Sophus::SE3f& pose = Sophus::SE3f()
        );

  void setPose(const Sophus::SE3f& T_cam_rel_map);
  /**
   * @brief Draw the camera keyframe as well as the frustrum.
   *
   * The frustrum is useful since it gives you an idea of the direction
   * it's facing.
   */
  void draw();

  Sophus::SE3f pose;
  Eigen::Vector3f frustum[4], updated_frustum[4];
  unsigned int width, height;
  float focal_length;
  Eigen::Vector2f principal_point;
};

typedef std::unique_ptr<Camera> CameraPtr;


/*****************************************************************************
** Trailers
*****************************************************************************/

} // namespace qglv

#endif /* qglv_objects_CAMERA_HPP_ */
