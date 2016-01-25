/**
 * @file /include/qglv/objects/keyframes.hpp
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef qglv_OBJECTS_KEYFRAME_HPP_
#define qglv_OBJECTS_KEYFRAME_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <memory>

#include "../gl/colours.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qglv {

/*****************************************************************************
** KeyFrame
*****************************************************************************/

/**
 * Data for each depth frame. This essentially packages the
 * statistics gathered DepthFrame with a structure that can be
 * neatly packaged off to the gui thread for consumption.
 *
 * It does some pre-computation before sending, and gllists
 * computation after arriving. Also, once it is sent off to
 * the gui receiver to be invoked the gui thread, local control
 * over the object is surrendered to the gui thread.
 *
 * It is also possible to generate keyframes from point clouds.
 * Refer to the qglv_pcl package for api.
 */
class KeyFrame 
{
public:
  KeyFrame()
  : id(-1)
  , pinned(false)
  , updated(false)
  , gl_id_start(-1)
  , axis_colour_scheme(AxisColourRGB)
  , axis_scale_factor(1.0)
  {}

  /**
   * Generate without any cloud information;
   */
  KeyFrame(const int id,
           const Sophus::SE3f& T_frame_rel_map,
           const AxisColourScheme& axis_colour_scheme=AxisColourRGB,
           const float& axis_scale_factor=1.0);
  
  /**
   * Generate from simple dslam pc keyframe data.
   */
  KeyFrame(const int id,
           const Sophus::SE3f& T,
           const bool& pinned,
           const std::vector< Eigen::Vector3f > & seeds, 
           const std::vector<float> & seed_variances,
           const std::vector<unsigned char>& seed_intensities, // intensity
           const float& focal_length_times_baseline
          );

  /**
   * Generate from simple dslam pc keyframe data.
   */
  KeyFrame(const int id,
           const Sophus::SE3f& T,
           const bool& pinned,
           const std::vector<float> & nics,
           const std::vector<float> & idepths, 
           const std::vector<float> & seed_variances,
           const std::vector<unsigned char>& seed_intensities_and_grad, // it consists of intensity, gx, gy. you have to use intensity
           const float& focal_length_times_baseline
          );
  /**
   * Generate from a tracking frame.
   */
  KeyFrame(
           const Sophus::SE3f& T,
           const std::vector<float> & nics,
           const std::vector<float> & idepths, 
           const std::vector<float> & seed_variances,
           const std::vector<unsigned char>& seed_intensities_and_grad // as a ratio, to convert to rgb. // it consists of intensity, gx, gy. you have to use intensity
          );
  ~KeyFrame();


  void setName(const std::string& name);
  void draw(
      bool draw_frames = true,
      bool draw_seeds = false,
      bool draw_covariances = false
      );

  int id;                       /**< @brief Id number of this frame **/
  Sophus::SE3f T_frame_rel_map; /**< @brief 6D information **/
  AxisColourScheme axis_colour_scheme;
  float axis_scale_factor;
  static const float default_keyframe_size;
  bool pinned;                  /**< @brief If the keyframe is pinned, we draw it differently. **/
  bool updated;                 /** @brief Flag denoting if it was new/updated recently. **/
  std::vector<unsigned char> intensities; // N*3
  std::vector<float> vertices;
  std::vector<float> variance_lines;

private:
  void _glGenLists();

  int gl_id_start;              /**< @brief Opengl id starting point for the lists. **/
  std::string name;
};

/*****************************************************************************
 ** Typedefs
 *****************************************************************************/

typedef std::shared_ptr<KeyFrame> KeyFramePtr;

} // namespace qglv

#endif /* qglv_OBJECTS_KEYFRAME_HPP_ */
