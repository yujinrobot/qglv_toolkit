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

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qglv {
namespace cv {

/*****************************************************************************
** Converters
*****************************************************************************/

std::pair<::cv::Mat, QImage> matToQImage(const ::cv::Mat &inMat);
std::pair<::cv::Mat, QPixmap> matToQPixmap(const ::cv::Mat &inMat);

} // namespace cv
} // namespace qglv

#endif /* qglv_OPENCV_HPP_ */
