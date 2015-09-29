/**
 * @file /src/lib/teleport_arrow.cpp
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <qglv/opengl.hpp>
#include <QGLViewer/qglviewer.h>
#include "../../include/qglv/objects/teleport_arrow.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qglv {

/*****************************************************************************
** Implementation
*****************************************************************************/

// this must be here, not in the header or you get undefined reference to vtable
TeleportArrow::~TeleportArrow() {}

void TeleportArrow::activate(bool mode) {
  teleport_mode_activated = mode;
}

void TeleportArrow::checkIfGrabsMouse(int x, int y, const qglviewer::Camera* const camera) {
  // MovableObject is active in a region of 5 pixels around its pos.
  // May depend on the actual shape of the object. Customize as desired.
  // Once clicked (moved = true), it keeps grabbing mouse until button is released.
  setGrabsMouse( teleport_mode_activated );
}

void TeleportArrow::mousePressEvent( QMouseEvent* const event, qglviewer::Camera* const camera) {
  begin_point = _pointOnZPlane(event->pos(), camera);
  end_point = _pointOnZPlane(event->pos(), camera);
  moving = true;
}

void TeleportArrow::mouseReleaseEvent(QMouseEvent* const event, qglviewer::Camera* const camera) {
  teleport_mode_activated = false;
  moving = false;
  emit deactivated();
  emit teleport(begin_point.x, begin_point.y, end_point.x, end_point.y);
}

void TeleportArrow::mouseMoveEvent(QMouseEvent* const event, qglviewer::Camera* const camera)
{
  if (moving) {
    end_point = _pointOnZPlane(event->pos(), camera);
  }
}

qglviewer::Vec TeleportArrow::_pointOnZPlane(const QPoint& point, const qglviewer::Camera* camera) const {
  qglviewer::Vec origin, direction, point_under_pixel, point_on_z_plane;
  camera->convertClickToLine(point, origin, direction);
  bool found;
  point_under_pixel = camera->pointUnderPixel(point, found);
  float alpha = - origin.z / direction.z;
  point_on_z_plane.x = origin.x + alpha*direction.x;
  point_on_z_plane.y = origin.y + alpha*direction.y;
  point_on_z_plane.z = 0.0;
  return point_on_z_plane;
}
void TeleportArrow::mouseDoubleClickEvent(QMouseEvent* const event, qglviewer::Camera* const camera) {
  Q_UNUSED(event);
  Q_UNUSED(camera);
  std::cout << "Double click event"<< std::endl;
}
void TeleportArrow::wheelEvent(QWheelEvent* const event, qglviewer::Camera* const camera) {
  Q_UNUSED(event);
  Q_UNUSED(camera);
  std::cout << "Wheel event"<< std::endl;
}

void TeleportArrow::draw()
{
  if ( grabsMouse() ) {
    if (moving) {
      qreal radius = 0.02;
      qglv::colour(Green);
      QGLViewer::drawArrow(begin_point, end_point, radius, 30);
    }
  }
}

} // namespace qglv
