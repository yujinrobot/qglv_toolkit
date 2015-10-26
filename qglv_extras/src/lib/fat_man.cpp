/**
 * @file /qglv/src/lib/objects/fat_man.cpp
 */
/*****************************************************************************
** Includes
*****************************************************************************/

#include <qglv/opengl.hpp>
#include "../../include/qglv/objects/fat_man.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qglv {

/*****************************************************************************
** C&D
*****************************************************************************/

FatMan::FatMan(const Sophus::SE3f& pose)
: updated(false)
, moving(false)
, gl_id_start(-1)
, pose(pose)
{
}

FatMan::~FatMan() {
  if ( gl_id_start > 0 ) {
    glDeleteLists(gl_id_start, 3);
  }
}

/*****************************************************************************
** Mouse
*****************************************************************************/

void FatMan::checkIfGrabsMouse(int x, int y, const qglviewer::Camera* const camera)
{
  // might be faster doing this comparison in screen coordinates, but less accurate
  Eigen::Vector3f z_plane_position = _pointOnZPlane(QPoint(x,y), camera);
  float distance = (z_plane_position - pose.translation()).norm();
  setGrabsMouse( moving || distance < 0.5 );
}

void FatMan::mousePressEvent( QMouseEvent* const event, qglviewer::Camera* const camera) {
  moving = true;
}

void FatMan::mouseMoveEvent(QMouseEvent* const event, qglviewer::Camera* const camera)
{
  if (moving)
  {
    // qglviewer should be doing draw() and mouse event handlers in the one thread
    // so no chance of conflict -> don't worry about guarding with mutex
    pose = Sophus::SE3f(Eigen::Matrix3f::Identity(), _pointOnZPlane(event->pos(), camera));
  }
}
void FatMan::mouseReleaseEvent(QMouseEvent* const event, qglviewer::Camera* const camera) {
  moving = false;
  // qglviewer should be doing draw() and mouse event handlers in the one thread
  // so no chance of conflict -> don't worry about guarding with mutex
  pose = Sophus::SE3f(Eigen::Matrix3f::Identity(), _pointOnZPlane(event->pos(), camera));
  emit moved(pose.translation().x(), pose.translation().y());
}

void FatMan::wheelEvent(QWheelEvent* const event, qglviewer::Camera* const camera) {
  Q_UNUSED(event);
  Q_UNUSED(camera);
  // don't know of any way to redirect this event back to the main qgl viewer window.
}

Eigen::Vector3f FatMan::_pointOnZPlane(const QPoint& point, const qglviewer::Camera* camera) const {
  qglviewer::Vec origin, direction, point_under_pixel;
  camera->convertClickToLine(point, origin, direction);
  bool found;
  point_under_pixel = camera->pointUnderPixel(point, found);
  float alpha = - origin.z / direction.z;
  Eigen::Vector3f point_on_z_plane;
  point_on_z_plane << origin.x + alpha*direction.x,
                      origin.y + alpha*direction.y,
                      0.05;
  return point_on_z_plane;
}

/*****************************************************************************
** Drawing
*****************************************************************************/

void FatMan::draw()
{
  if (gl_id_start == -1) {
    _glGenLists();
  }
  glPushMatrix();
  qglv::moveTo(pose.inverse());
  if ( moving ) {
    qglv::colour(DimGray);
  } else {
    qglv::colour(GoldenBrown);
  }
  glCallList(gl_id_start);
  glPopMatrix();
}

void FatMan::_glGenLists() {
  gl_id_start = ::glGenLists(1);

  glNewList( gl_id_start, GL_COMPILE );
  glBegin(GL_TRIANGLE_FAN);
  glVertex2f( 0.5,  0.0);
  glVertex2f( 0.353,  0.353);
  glVertex2f( 0.0,  0.5);
  glVertex2f( -0.353,  0.353);
  glVertex2f(-0.5,  0.0);
  glVertex2f( -0.353,  -0.353);
  glVertex2f( 0.0, -0.5);
  glVertex2f( 0.353,  -0.353);
  glEnd();
  qglv::colour(White);
  qglv::text("Fat Man", Eigen::Vector3f(-0.25,0.005,0.2));
  glEndList();
}


/*****************************************************************************
 ** Trailers
 *****************************************************************************/

} // namespace qglv
