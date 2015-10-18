/**
 * @file /include/qglv/objects/fat_man.hpp
 */
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef qglv_OBJECTS_FAT_MAN_HPP_
#define qglv_OBJECTS_FAT_MAN_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

//#include <dslam_math_helpers/sophus.hpp>
#include <Eigen/Core>
#include <memory>
#include <QGLViewer/qglviewer.h>
#include <QGLViewer/mouseGrabber.h>
#include <QMouseEvent>
#include <QObject>
#include <QWheelEvent>
#include <QPoint>
#include <sophus/se3.hpp>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qglv {

/*****************************************************************************
** The Fat Man
*****************************************************************************/
/**
 * Fat men are great tests for obstacles. This renders a dummy
 * 3d volume for the fat man which can be moved around on a qgl canvas.
 *
 * Optionally takes a pose (not transform) for the fatman. e.g. for a 2d configuration
 *
 * @code
 * Sophus::SE3f(Eigen::Matrix3f::Identity(), Eigen::Vector3f(-3.0f, 1.0f, 0.0f));
 * @endcode
 */
class FatMan : public QObject, qglviewer::MouseGrabber {
  Q_OBJECT
public:
  FatMan(const Sophus::SE3f& pose = Sophus::SE3f());
  virtual ~FatMan();

  void checkIfGrabsMouse(int x, int y, const qglviewer::Camera* const camera);
  virtual void mousePressEvent( QMouseEvent* const event, qglviewer::Camera* const camera);
  virtual void mouseMoveEvent(QMouseEvent* const event, qglviewer::Camera* const camera);
  virtual void mouseReleaseEvent(QMouseEvent* const event, qglviewer::Camera* const camera);
  virtual void wheelEvent(QWheelEvent* const event, qglviewer::Camera* const camera);

  Eigen::Vector3f position() const { return pose.translation(); }

  void draw();

signals:
  void moved(const float&, const float&);

private:
  bool updated;                 /**< @brief Flag denoting if it was new/updated recently. **/
  bool moving;                  /**< @brief In the middle of being moved by the mouse **/
  int gl_id_start;              /**< @brief Opengl id starting point for the lists. **/
  Sophus::SE3f pose;            /**< @brief 6D information, pose, not transform! **/

  void _glGenLists();
  // TODO : move this off to a common method somewhere
  Eigen::Vector3f _pointOnZPlane(const QPoint& point, const qglviewer::Camera* camera) const;
};

/*****************************************************************************
 ** Typedefs
 *****************************************************************************/

typedef std::shared_ptr<FatMan> FatManPtr;

/*****************************************************************************
** Trailers
*****************************************************************************/

} // namespace qglv

#endif /* qglv_OBJECTS_FAT_MAN_HPP_ */
