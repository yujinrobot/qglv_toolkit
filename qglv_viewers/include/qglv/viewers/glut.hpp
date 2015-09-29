/**
 * @file /qglv/include/qglv/gl/glut.hpp
 * 
 * @brief Short description of this file.
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef qglv_GLUT_HPP_
#define qglv_GLUT_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <GL/gl.h>
#include <QGLViewer/qglviewer.h>

/*****************************************************************************
** Interfaces
*****************************************************************************/

/**
 * libqglviewer has a bug which prevents from running without linking to
 * glut. Since g++ also strips that dependency from our binaries if there
 * are no other glut operations, we need at least one 'dummy' glut
 * operation in this library.
 */
GLUquadricObj* glutFoo();

#endif /* qglv_GLUT_HPP_ */
