/**
 * @file /qglv/include/qglv/objects/path.hpp
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef qglv_OBJECTS_PATH_HPP_
#define qglv_OBJECTS_PATH_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <deque>
#include <memory>
#include <sophus/se3.hpp>
#include <vector>

#include "../gl/colours.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qglv {

/*****************************************************************************
** Interfaces
*****************************************************************************/

/**
 * Draws arrows aligned with each accumulated pose frame.
 *
 * - arrows are rendered together in a gl list
 * - colour and radius specified in the constructor
 * - length can be in the constructor also, or in each add() command to represent
 *   varying quantities (like actual length to the next pose).
 */
class Path {
public:
  Path(const Colour& colour = Magenta,
       const float& arrow_radius = 0.01,
       const float& default_length = 0.3);
  ~Path();

  void add(const Sophus::SE3f& pose);
  void add(const Sophus::SE3f& pose, const float& length);
  void draw();

private:
  int gl_id;
  bool need_to_rebuild_gl_list;
  float arrow_radius, default_length;
  Colour colour;

  std::vector<std::pair<Sophus::SE3f, float>> data;
  void _glGenLists();
};

/*****************************************************************************
 ** Typedefs
 *****************************************************************************/

typedef std::shared_ptr<Path> PathPtr;


/*****************************************************************************
 ** Trailers
 *****************************************************************************/

} // namespace qglv

#endif /* qglv_OBJECTS_PATH_HPP_ */
