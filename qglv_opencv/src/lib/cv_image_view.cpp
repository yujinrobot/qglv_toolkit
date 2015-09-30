/**
 * @file /src/lib/cv_image_view.cpp
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <opencv2/opencv.hpp>
#include <QImage>
#include <QMetaType>
#include <QPixmap>
#include "../../include/qglv/opencv.hpp"
#include "../../include/qglv/widgets/cv_image_view.hpp"

/*****************************************************************************
** Macros
*****************************************************************************/

Q_DECLARE_METATYPE(cv::Mat);

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qglv {

/*****************************************************************************
** Implementation
*****************************************************************************/

CvImageView::CvImageView(QWidget *parent)
: QGraphicsView(parent)
, scene(nullptr)
{
  qRegisterMetaType<cv::Mat>("OpencvMat");

  // no need for scrollbars - we always scale
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  // set the scene
  scene = new QGraphicsScene(this);
  setScene(scene);

//  cv::Mat image;
//  image = cv::imread("/home/snorri/images/slam.png", CV_LOAD_IMAGE_COLOR);
//  showImage(image);
}

/*****************************************************************************
 ** Events
 *****************************************************************************/

void CvImageView::showEvent(QShowEvent *) {
  fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
}

void CvImageView::resizeEvent(QResizeEvent* event)
{
  QGraphicsView::resizeEvent(event);
  fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
}

/*****************************************************************************
 ** Custom Methods
 *****************************************************************************/

void CvImageView::show404Image() {
  std::cout << "Showing 404 image" << std::endl;
  QPixmap pixmap(":/images/never.jpg");
  scene->clear();
  scene->addPixmap(pixmap);
  fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void CvImageView::showImage(cv::Mat image) {
  if ( image.empty() ) {
    show404Image();
  } else {
    std::pair<cv::Mat, QPixmap> pair = qglv::opencv::matToQPixmap(image);
    image_internal_storage = pair.first;
    scene->clear();
    scene->addPixmap(pair.second);
    fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
  }
}

} // namespace qglv
