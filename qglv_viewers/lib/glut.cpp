/**
 * @file /qglv/src/lib/gl/glut.cpp
 * 
 * @brief Short description of this file.
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <GL/gl.h>
#include <QGLViewer/qglviewer.h>
#include "../../../include/qglv/gl/glut.hpp"

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
