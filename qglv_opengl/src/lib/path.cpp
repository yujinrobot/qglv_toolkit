/**
 * @file /src/lib/path.cpp
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include "../../include/qglv/gl/headers.hpp"
#include "../../include/qglv/objects/path.hpp"
#include "../../include/qglv/primitives/arrow.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qglv {

/*****************************************************************************
 ** Path
 *****************************************************************************/

Path::Path(const Colour& colour, const float& arrow_radius, const float& default_length)
: gl_id(-1)
, need_to_rebuild_gl_list(false)
, arrow_radius(arrow_radius)
, default_length(default_length)
, colour(colour)
{
}

Path::~Path() {
  if ( gl_id > 0 ) {
    glDeleteLists(gl_id, 1);
  }
}

void Path::add(const Sophus::SE3f& pose) {
  add(pose, default_length);
}

void Path::add(const Sophus::SE3f& pose, const float& length) {
  data.push_back(std::pair<Sophus::SE3f, float>(pose, length));
  need_to_rebuild_gl_list = true;
}

void Path::_glGenLists() {
  if ( need_to_rebuild_gl_list ) {
    if ( gl_id > 0 ) {
      glDeleteLists(gl_id, 1);
    }
    gl_id = ::glGenLists(1);
    glNewList( gl_id, GL_COMPILE );
    qglv::colour(colour);
    for ( const auto& pose_length : data ) {
      qglv::arrow(pose_length.first, pose_length.second, arrow_radius);
    }
    glEndList();
  }
}

void Path::draw() {
  if ( need_to_rebuild_gl_list ) {
    _glGenLists();
    need_to_rebuild_gl_list = false;
  }
  glPushMatrix();
  if (gl_id > 0) {
    glCallList(gl_id);
  }
  glPopMatrix();
}

/*****************************************************************************
 ** Trailers
 *****************************************************************************/

} // namespace qglv
