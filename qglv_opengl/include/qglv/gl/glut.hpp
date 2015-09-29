/**
 * @file /include/qglv/gl/glut.hpp
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef qglv_GL_GLUT_HPP_
#define qglv_GL_GLUT_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include "headers.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qglv {

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

}  // namespace qglv

/*****************************************************************************
** Trailers
*****************************************************************************/

#endif /* qglv_GL_GLUT_HPP_ */
