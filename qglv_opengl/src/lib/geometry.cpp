/**
 * @file /qglv_opengl/src/lib/geometry.cpp
 */
/*****************************************************************************
 ** Includes
 *****************************************************************************/

#include "../../include/qglv/gl/headers.hpp"
#include "../../include/qglv/primitives/geometry.hpp"

/*****************************************************************************
 ** Namespaces
 *****************************************************************************/

namespace qglv {

/*****************************************************************************
 ** Implementation
 *****************************************************************************/

void line(const Eigen::Vector3f & p1, const Eigen::Vector3f & p2) {
  glBegin(GL_LINES);
  glVertex3f(static_cast<float>(p1[0]), static_cast<float>(p1[1]), static_cast<float>(p1[2]));
  glVertex3f(static_cast<float>(p2[0]), static_cast<float>(p2[1]), static_cast<float>(p2[2]));
  glEnd();
}

void point(const Eigen::Vector3f & p, const float size) {
  glEnable(GL_POINT_SMOOTH);

  glPointSize(size);
  glBegin(GL_POINTS);
  glVertex3f(p.x(), p.y(), p.z());
  glEnd();

  glDisable(GL_POINT_SMOOTH);
}

void points(const std::vector<Eigen::Vector3f, Eigen::aligned_allocator<Eigen::Vector3f> > & p, const float size) {
  glEnable(GL_POINT_SMOOTH);

  glPointSize(size);

  for (int i(0); i < p.size(); i++)
  {
    glBegin(GL_POINTS);
    glVertex3f(p[i].x(), p[i].y(), p[i].z());
    glEnd();
  }

  glDisable(GL_POINT_SMOOTH);
}

void vertex(const Eigen::Vector3f& p)
{
  glVertex3f(p.x(), p.y(), p.z());
}

void square(const float &width, const float& height) {
  glBegin(GL_QUADS); // Start drawing a quad primitive
  glVertex3f(0.0f, 0.0f, 0.0f); // The bottom left corner
  glVertex3f(0.0f, height, 0.0f); // The top left corner
  glVertex3f(width, height, 0.0f); // The top right corner
  glVertex3f(width, 0.0, 0.0f); // The bottom right corner
  glEnd();
}

/*****************************************************************************
 ** Trailers
 *****************************************************************************/

} // namespace qglv
