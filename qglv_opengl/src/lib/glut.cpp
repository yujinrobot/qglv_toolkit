/**
 * @file /src/lib/glut.cpp
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include "../../include/qglv/gl/glut.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qglv {

/*****************************************************************************
 ** Implementation
 *****************************************************************************/

GLUquadricObj* glutFoo() {
  GLUquadricObj* quadric;
  gluQuadricDrawStyle(quadric, GLU_FILL);
  gluQuadricNormals(quadric, GLU_SMOOTH);
  return quadric;
}

//GLUquadricObj* quadric = glutFoo();

} // namespace qglv
