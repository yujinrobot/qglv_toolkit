/**
 * @file /include/qglv/objects/reference_frames.hpp
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef qglv_OBJECTS_REFERENCE_FRAMES_HPP_
#define qglv_OBJECTS_REFERENCE_FRAMES_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <map>
#include <memory>
#include <qglv/opengl.hpp>
#include <sophus/se3.hpp>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qglv {

/*****************************************************************************
** ReferenceFrame
*****************************************************************************/

/**
 * Show just a frame floating in free space with a single line
 * linking it back to its parent (think tf's in ROS).
 */
class ReferenceFrame {
public:
  enum Label {
    Map = 0,
    VisualOdom,
    Odom
  };

  ReferenceFrame(
      const std::string& name,
      const Sophus::SE3f& T,
      const Colour &colour=Yellow,
      const Sophus::SE3f& parent=Sophus::SE3f(Eigen::Matrix3f::Identity(), Eigen::Vector3f::Zero())
  );
  ~ReferenceFrame();

  void draw();

  Sophus::SE3f T_frame_rel_map; /**< @brief 6D information **/
  std::string name;             /**< @brief Name of this frame, exposed so we can draw a label on the frame in the qgl viewer **/

  static const float default_keyframe_size;

private:
  void _glGenLists();
  Colour colour;
  int gl_id_start;              /**< @brief Opengl id starting point for the lists. **/
};

/*****************************************************************************
 ** Typedefs
 *****************************************************************************/

typedef std::shared_ptr<ReferenceFrame> ReferenceFramePtr;
typedef std::map<ReferenceFrame::Label, ReferenceFramePtr> ReferenceFrames;

} // namespace qglv

#endif /* qglv_OBJECTS_REFERENCE_FRAMES_HPP_ */
