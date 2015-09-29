/**
 * @file /qglv_opengl/src/lib/text.cpp
 */
/*****************************************************************************
** Includes
*****************************************************************************/

#include "../../include/qglv/gl/headers.hpp"
#include "../../include/qglv/primitives/text.hpp"

// must be after including gl/headers.hpp - can we get rid of this dep.?
#include <GL/glut.h>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qglv {

/*****************************************************************************
** Implementation
*****************************************************************************/

void text( const std::string & str, const Eigen::Vector3f & location )
{
  static bool glut_initialised(false);

  if( !glut_initialised )
  {
    int argc=1;
    char * argv[1];
    argv[0] = (char *)"glServer";

    glutInit(&argc, argv);
    glut_initialised = true;
  }
  // if we wanted to centre align, however we don't seem to have gluBitmapWidth
  // float length = 0.0;
  // for ( const char& c : str ) {
  //   length += gluBitmapWidth(GLUT_BITMAP_HELVETICA_12);
  // }
  glRasterPos3f( location.x(), location.y(), location.z() );

  for( int i(0); i < str.size(); i++)
  {
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_12, str[i] );
  }
}

/*****************************************************************************
 ** Trailers
 *****************************************************************************/

} // namespace qglv
