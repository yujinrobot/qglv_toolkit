/**
 * @file /qglv/include/qglv/objects/odometry.hpp
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef qglv_OBJECTS_ODOMETRY_HPP_
#define qglv_OBJECTS_ODOMETRY_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <deque>
#include <memory>
#include <sophus/se3.hpp>
#include <vector>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qglv {

/*****************************************************************************
** Interfaces
*****************************************************************************/

class Odometry {
public:
  Odometry(const Sophus::SE3f& T_extrinsics);
  ~Odometry();

  void update(const Sophus::SE3f& T_cam_rel_odom);
  void draw();
  void draw(const Sophus::SE3f& T_map_rel_odom);

  int gl_id_global, gl_id_window;
  std::vector<Sophus::SE3f> global; /**< Stores a dispersed sample of odometry frame poses (T_cam_rel_odom.inverse() transforms) **/
  std::deque<Sophus::SE3f> window;  /**< Stores the last n odometry poses (T_cam_rel_odom.inverse() transforms) **/

private:
  Sophus::SE3f T_extrinsics_rotation;  // this is rotation part of T_extrinsics (lets us convert camera rotation to align with base, i.e. robot front).
  void _glGenLists();
  bool need_to_rebuild_global_list, need_to_rebuild_window_list;
  unsigned int size_of_odometry_trail;
};

/*****************************************************************************
 ** Typedefs
 *****************************************************************************/

typedef std::shared_ptr<Odometry> OdometryPtr;

/*****************************************************************************
 ** Trailers
 *****************************************************************************/

} // namespace qglv

#endif /* qglv_OBJECTS_ODOMETRY_HPP_ */
