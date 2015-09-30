/**
 * @file /include/qglv/widgets/cv_image_view.hpp
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef qglv_WIDGETS_CV_IMAGE_VIEW_HPP_
#define qglv_WIDGETS_CV_IMAGE_VIEW_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <opencv2/core/core.hpp>

#include <QGraphicsScene>
#include <QGraphicsView>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qglv {

/*****************************************************************************
** Interfaces
*****************************************************************************/

class CvImageView : public QGraphicsView
{
  Q_OBJECT

public:
  CvImageView(QWidget *parent = 0);

public slots:
  void showImage(cv::Mat image);
  void show404Image();

protected:
  void showEvent(QShowEvent *);
  void resizeEvent(QResizeEvent* event);

private:
  QGraphicsScene* scene;
  cv::Mat image_internal_storage; // required as QImage always needs an external buffer.
};

} // namespace qglv

#endif /* qglv_WIDGETS_CV_IMAGE_VIEW_HPP_ */
