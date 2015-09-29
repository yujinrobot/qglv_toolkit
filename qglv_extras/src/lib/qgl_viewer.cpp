/**
 * @file /src/lib/qgl_viewer.cpp
 */
/*****************************************************************************
** Includes
*****************************************************************************/

#include <qglv/opengl.hpp>
#include <QDateTime>
#include "../../include/qglv/widgets/qgl_viewer.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qglv {

/*****************************************************************************
** Implementation
*****************************************************************************/

QGLViewer::QGLViewer(QWidget *parent)
: ::QGLViewer(parent)
, last_redraw_(0)
, redraw_interval_ms_(20)
{
  // MouseBindings need to be here so the mouseString gets modified for use early.
  setMouseTracking(true);
  setMouseBinding(Qt::ControlModifier, Qt::LeftButton, CAMERA, SCREEN_ROTATE);
  setMouseBinding(Qt::NoModifier, Qt::LeftButton | Qt::RightButton, CAMERA, SCREEN_ROTATE);
}

QGLViewer::~QGLViewer() {}

void QGLViewer::init() {

  GLenum err = glewInit();
  if (err != GLEW_OK)
  {
    std::cout << "ERROR : failed to initialise glew" << std::endl;
    // TODO abort or exceptions here
  }
  /****************************************
   ** QGL Defaults
   ****************************************/
  setForegroundColor(QColor(80, 80, 80));  // defaults are 180
  setBackgroundColor(QColor(0, 0, 0));        // defaults are 51

  // setAxisIsDrawn(); // we draw our own axis
  // setGridIsDrawn(); // we draw our own grid
  setSceneRadius(6.0);
  showEntireScene();
  setSceneRadius(20.0);  // cheap hack in getting the camera to first zoom in, and then set a large scene for defining clipping planes

  // libqglviewer by default sets the following (see the docs)
//  glEnable(GL_LIGHT0);
//  glEnable(GL_LIGHTING);
//  glEnable(GL_DEPTH_TEST);
//  glEnable(GL_COLOR_MATERIAL);
//  // libQGL enables lighting, but default lighting makes frames hard to read, so set some ambient light
//  GLfloat light_ambient[] = {0.8, 0.8, 0.8, 1.0};
//  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glDisable(GL_LIGHTING);

  last_redraw_ = QDateTime::currentMSecsSinceEpoch();

//  restoreStateFromFile();

  // Enable direct frame manipulation when the mouse hovers.
//  setMouseTracking(true);
  //setMouseBinding(Qt::AltModifier, Qt::RightButton, QGLViewer::FRAME, QGLViewer::ROTATE);
//  setKeyDescription(Qt::Key_Plus, "Increases interpolation speed");
//  setKeyDescription(Qt::Key_Minus, "Decreases interpolation speed");
//  setKeyDescription(Qt::Key_Left, "Selects previous key frame");
//  setKeyDescription(Qt::Key_Right, "Selects next key frame");
//  setKeyDescription(Qt::Key_Return, "Starts/stops interpolation");
  // help(); // don't call qglviewer's help object, we send our help, keyboard, mouse strings to a higher level window.

}

/*****************************************************************************
 ** Events
 *****************************************************************************/

//void QGLViewer::mouseMoveEvent(QMouseEvent *e)
//{
////  std::cout << "e->button(): " << e->button() << std::endl;  // always zero
////  std::cout << "e->modifiers(): " << e->modifiers() << std::endl;  // always zero
////  std::cout << "e->x(): " << e->x() << std::endl;
////  std::cout << "e->y(): " << e->x() << std::endl;
//  if (( ecl::TimeStamp() - last_show_image_ ) > show_image_interval_) {
//    signalImagesToShow_(e->pos());
//    last_show_image_ = ecl::TimeStamp();
//  }
//  QGLViewer::mouseMoveEvent(e);
//}

//void QGLViewer::keyPressEvent(QKeyEvent *e)
//{
//  switch (e->key())
//        {
//        default:
//          QGLViewer::keyPressEvent(e);
//        }
//}

/*****************************************************************************
 ** Help
 *****************************************************************************/

QString QGLViewer::helpString() const
{
  QString text("<h2>DSlam QGL Viewer </h2>");
  text += "Common qgl viewer class for dslam applications.<br/>";
  text += "<br/>";
  text += "<b>Specifications</b><br/>";
  text += "<br/>";
  text += "<i>Grid Cells</i> : 1mx1m.<br/>";
  text += "<br/>";
  return text;
}

/*****************************************************************************
 ** Drawing
 *****************************************************************************/

void QGLViewer::redraw() {
  if (( QDateTime::currentMSecsSinceEpoch() - last_redraw_ ) > redraw_interval_ms_) {
    updateGL();
    last_redraw_ = QDateTime::currentMSecsSinceEpoch();
  }
}

void QGLViewer::draw()
{
  /********************
   ** World Setup
   ********************/
  qglColor(foregroundColor());

  // TODO : figure out a good 'scale' mapping metres to OpenGL units for everything
  // this will effect our grid dimensions below and the way we draw objects.
  glLineWidth(0.5); drawGrid(40.0f, 80);  // currently, size is centre->edge (in metres), subdivisions

//  /****************************************
//   ** State
//   ****************************************/
//  float cached_colour[4], cached_line_width;
//  glGetFloatv(GL_CURRENT_COLOR, cached_colour);
//  glGetFloatv(GL_LINE_WIDTH, &cached_line_width);
//
//  /****************************************
//   ** Restoration
//   ****************************************/
//  glLineWidth(cached_line_width);
//  glColor4f(cached_colour[0], cached_colour[1], cached_colour[2], cached_colour[3]);
}

/*****************************************************************************
 ** Trailers
 *****************************************************************************/

} // namespace qglv
