/**
 * @file /qglv/include/qglv/objects/edges.hpp
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef qglv_OBJECTS_EDGES_HPP_
#define qglv_OBJECTS_EDGES_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <memory>
#include <sophus/se3.hpp>
#include <vector>

#include "../gl/colours.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qglv {

/*****************************************************************************
** Edges
*****************************************************************************/

/**
 * Edges in a form ready to draw on an opengl canvas.
 *
 * Currently we don't need to update this class as I only create it on
 * loading. In future however, we might want to handle this in a dynamic
 * way to reuse it for the dslam runtime monitor as well.
 */
class Edges {

public:
  Edges();
  virtual ~Edges();
  void add(const Sophus::SE3f& T_start, const Sophus::SE3f& T_end);
  void draw();
  void clear();


private:
  virtual void _glGenLists();
  bool updated;
  int gl_id; /**< @brief Opengl id starting point for the lists. **/

  std::vector< float > vertice_array;
};


/*****************************************************************************
** Edges
*****************************************************************************/

/**
 * Directed version of the previous edges.
 *
 * Currently we don't need to update this class as I only create it on
 * loading. In future however, we might want to handle this in a dynamic
 * way to reuse it for the dslam runtime monitor as well.
 */
class DirectedEdges {

public:
  DirectedEdges(const Colour& colour = Magenta, const float& radius = 0.005);
  virtual ~DirectedEdges();
  void add(const Sophus::SE3f& T_start, const Sophus::SE3f& T_end);
  void draw();
  void clear();

protected:
  virtual void _glGenLists();
  bool updated;
  int gl_id; /**< @brief Opengl id starting point for the lists. **/
  const Colour colour;
  const float radius;

  std::vector< std::pair<Sophus::SE3f, Sophus::SE3f> > transforms;
};

/*****************************************************************************
 ** Typedefs
 *****************************************************************************/

typedef std::shared_ptr<Edges> EdgesPtr;
typedef std::shared_ptr<DirectedEdges> DirectedEdgesPtr;


} // namespace qglv

#endif /* qglv_OBJECTS_EDGES_HPP_ */
