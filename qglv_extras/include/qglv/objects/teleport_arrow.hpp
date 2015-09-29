/**
 * @file /include/qglv/dslam_viewer/teleport_arrow.hpp
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef qglv_OBJECTS_TELEPORT_ARROW_HPP_
#define qglv_OBJECTS_TELEPORT_ARROW_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QGLViewer/qglviewer.h>
#include<QGLViewer/mouseGrabber.h>
#include <QMouseEvent>
#include <QObject>
#include <QPoint>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qglv {

/*****************************************************************************
** Interfaces
*****************************************************************************/

class TeleportArrow : public QObject, qglviewer::MouseGrabber
{
  Q_OBJECT
public:
  TeleportArrow()
  : begin_point(0,0,0)
  , end_point(0,0,0)
  , moving(false)
  , teleport_mode_activated(false)
  {}

  ~TeleportArrow();

  void checkIfGrabsMouse(int x, int y, const qglviewer::Camera* const camera);
  virtual void mousePressEvent( QMouseEvent* const event, qglviewer::Camera* const camera);
  virtual void mouseReleaseEvent(QMouseEvent* const event, qglviewer::Camera* const camera);
  virtual void mouseMoveEvent(QMouseEvent* const event, qglviewer::Camera* const camera);
  virtual void mouseDoubleClickEvent(QMouseEvent* const event, qglviewer::Camera* const camera);
  virtual void wheelEvent(QWheelEvent* const event, qglviewer::Camera* const camera);

  void draw();

public slots:
  void activate(bool mode);

signals:
  void deactivated();
  void teleport(float, float, float, float);

private:
  qglviewer::Vec _pointOnZPlane(const QPoint& point, const qglviewer::Camera* camera) const;

  qglviewer::Vec begin_point, end_point;
  bool moving;
  bool teleport_mode_activated;
};

} // qglv

#endif /* qglv_OBJECTS_TELEPORT_ARROW_HPP_ */
