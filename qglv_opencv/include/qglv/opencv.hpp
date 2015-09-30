/**
 * @file include/qglv/opencv.hpp
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef qglv_OPENCV_HPP_
#define qglv_OPENCV_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QImage>
#include <QPixmap>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>

#include "widgets/cv_image_view.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qglv {
namespace opencv {

/*****************************************************************************
** Converters
*****************************************************************************/

std::pair<cv::Mat, QImage> matToQImage(const cv::Mat &inMat);
std::pair<cv::Mat, QPixmap> matToQPixmap(const cv::Mat &inMat);

} // namespace cv
} // namespace qglv

#endif /* qglv_OPENCV_HPP_ */
