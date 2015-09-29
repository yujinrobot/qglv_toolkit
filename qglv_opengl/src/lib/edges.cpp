/**
 * @file /src/lib/edges.cpp
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <Eigen/Core>
#include <Eigen/Geometry>

#include "../../include/qglv/gl/headers.hpp"
#include "../../include/qglv/primitives/arrow.hpp"
#include "../../include/qglv/objects/edges.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qglv {

/*****************************************************************************
** Edges
*****************************************************************************/

Edges::Edges()
 : updated(false)
 , gl_id(-1)
{
}

Edges::~Edges() {
  if ( gl_id > 0 ) {
    glDeleteLists(gl_id, 1);
  }
}

void Edges::add(const Sophus::SE3f& T_start, const Sophus::SE3f& T_end) {
  // convert into a convenient form for gl drawing
  Sophus::SE3f T_inv = T_start.inverse();
  vertice_array.push_back(T_inv.translation().x());
  vertice_array.push_back(T_inv.translation().y());
  vertice_array.push_back(T_inv.translation().z());
  T_inv = T_end.inverse();
  vertice_array.push_back(T_inv.translation().x());
  vertice_array.push_back(T_inv.translation().y());
  vertice_array.push_back(T_inv.translation().z());
  updated = true;
}

void Edges::clear() {
  vertice_array.clear();
  updated = true;
}

void Edges::draw() {
  if ( updated ) {
    _glGenLists();
  }
  ::glCallList(gl_id);
}

void Edges::_glGenLists() {
  gl_id = ::glGenLists(1);
  glNewList( gl_id, GL_COMPILE );
  glColor3f(0.1f, 0.2f, 0.1f);
  glLineWidth(0.1f);
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, vertice_array.data() );
  glDrawArrays(GL_LINES, 0, vertice_array.size() / 3 );
  glDisableClientState(GL_VERTEX_ARRAY);
  glEndList();
}

/*****************************************************************************
 ** Directed Edges
 *****************************************************************************/

DirectedEdges::DirectedEdges(const Colour& colour, const float& radius)
 : updated(false)
 , gl_id(-1)
 , colour(colour)
 , radius(radius)
{
}

DirectedEdges::~DirectedEdges() {
  if ( gl_id > 0 ) {
    glDeleteLists(gl_id, 1);
  }
}

void DirectedEdges::add(const Sophus::SE3f& T_start, const Sophus::SE3f& T_end) {
  transforms.push_back(std::pair<Sophus::SE3f, Sophus::SE3f>(T_start, T_end));
//  // convert into a convenient form for gl drawing
//  Sophus::SE3f T_inv = T_start.inverse();
//  vertice_array.push_back(T_inv.translation().x());
//  vertice_array.push_back(T_inv.translation().y());
//  vertice_array.push_back(T_inv.translation().z());
//  T_inv = T_end.inverse();
//  vertice_array.push_back(T_inv.translation().x());
//  vertice_array.push_back(T_inv.translation().y());
//  vertice_array.push_back(T_inv.translation().z());
  updated = true;
}

void DirectedEdges::clear() {
  transforms.clear();
  updated = true;
}

void DirectedEdges::draw() {
  if ( updated ) {
    _glGenLists();
  }
  if ( (gl_id > 0) ) {
    ::glCallList(gl_id);
  }
}

void DirectedEdges::_glGenLists() {
  if ( gl_id > 0 ) {
    glDeleteLists(gl_id, 1);
  }
  gl_id = ::glGenLists(1);
  glNewList( gl_id, GL_COMPILE );
  qglv::colour(colour);
  for ( const auto& transform_pair : transforms ) {
    Sophus::SE3f T_end_rel_start = transform_pair.second*transform_pair.first.inverse();
    float length = T_end_rel_start.inverse().translation().norm();
    Eigen::Vector3f new_x_axis = transform_pair.second.inverse().translation() - transform_pair.first.inverse().translation();
    Eigen::Quaternionf orientation = Eigen::Quaternionf::FromTwoVectors(Eigen::Vector3f::UnitX(), new_x_axis);
    Eigen::Vector3f translation = transform_pair.first.inverse().translation();
    Sophus::SE3f pose(orientation, translation);
    qglv::arrow(pose, length, radius);
  }
  glEndList();
  updated = false;
}


} // namespace qglv
