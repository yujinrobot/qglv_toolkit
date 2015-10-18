/**
 * @file /qglv_opengl/include/qglv/objects/particles.hpp
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef qglv_OBJECTS_PARTICLES_HPP_
#define qglv_OBJECTS_PARTICLES_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <memory>
#include <sophus/se3.hpp>
#include <vector>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qglv {

/*****************************************************************************
** Edges
*****************************************************************************/

/**
 * Draw a bunch of arrows representing sophus particles.
 *
 * Typically used for representation of a particle filter.
 */
class Particles {

public:
  Particles();
  virtual ~Particles();
  void add( std::vector< Sophus::SE3f > & newTransforms );
  void draw();
  void clear();
  bool empty();

private:
  virtual void _glGenLists();
  bool updated;
  int gl_id; /**< @brief Opengl id starting point for the lists. **/

  /// transforms
  std::vector< Sophus::SE3f > T;
};



/*****************************************************************************
 ** Typedefs
 *****************************************************************************/

typedef std::shared_ptr<Particles> ParticlesPtr;


} // namespace qglv

#endif /* qglv_OBJECTS_PARTICLES_HPP_ */
