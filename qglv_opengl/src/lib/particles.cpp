/**
 * @file /qglv_opengl/src/lib/particles.cpp
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include "../../include/qglv/gl/headers.hpp"
#include "../../include/qglv/objects/particles.hpp"
#include "../../include/qglv/primitives/arrow.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qglv {

/*****************************************************************************
** Particles
*****************************************************************************/

Particles::Particles()
 : updated(false)
 , gl_id(-1)
{
}

Particles::~Particles() 
{
  if ( gl_id > 0 ) {
    glDeleteLists(gl_id, 1);
  }
}

void Particles::add( std::vector< Sophus::SE3f > & newTransforms ) 
{
  T = newTransforms;
  updated = true;
}

bool Particles::empty()
{
  return T.empty();
}

void Particles::clear() 
{
  T.clear();
  updated = true;
}

void Particles::draw() {
  if ( updated ) 
  {
    _glGenLists();
  }
  ::glCallList(gl_id);
}

void Particles::_glGenLists() 
{
  if( gl_id < 0 ) gl_id = ::glGenLists(1);
  static const float draw_arrow_length = 0.3;
  static const float draw_arrow_radius = 0.01;
  
  glNewList( gl_id, GL_COMPILE );
  glColor3f(0.2f, 0.1f, 0.1f);
  
  
  for( int i(0); i<T.size(); i++ )
  {
    arrow(T[i].inverse(),
          0.3 * draw_arrow_length,
          0.5 * draw_arrow_radius
          );
  }
  
  glEndList();
}


} // namespace qglv
