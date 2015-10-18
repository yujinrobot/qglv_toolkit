/**
 * @file /include/qglv/widgets/qgl_viewer.hpp
 */
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef qglv_WIDGETS_COMMON_QGL_VIEWER_HPP_
#define qglv_WIDGETS_COMMON_QGL_VIEWER_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <qglv/opengl.hpp>
#include <QGLViewer/qglviewer.h>
#include <QString>
#include <QWidget>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qglv {

/*****************************************************************************
** Interfaces
*****************************************************************************/

/**
 * Common setup for dslam qgl viewers - subclass this for our applications.
 */
class QGLViewer : public ::QGLViewer
{
  Q_OBJECT
public :
  QGLViewer(QWidget *parent = nullptr);
  virtual ~QGLViewer();
  virtual void init();
  virtual QString helpString() const;  // overload this

  // virtual void keyPressEvent(QKeyEvent *e);
  // void mouseMoveEvent(QMouseEvent *e);
  // void mouseMoveEvent(QMouseEvent* const event, Camera* const camera);

  virtual void draw();

public slots:
  void redraw();

private:
  qint64 last_redraw_, redraw_interval_ms_;
};

/*****************************************************************************
** Trailers
*****************************************************************************/

} // namespace qglv

#endif /* qglv_WIDGETS_COMMON_QGL_VIEWER_HPP_ */
