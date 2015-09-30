/**
 * @file /dslam_viewer/src/lib/utilities/opencv.cpp
 * 
 * @brief Short description of this file.
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QDebug>  // for qWarning
#include <QImage>
#include <QPixmap>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>

#include "../../include/qglv/opencv.hpp"

// only for testing
// #include <cv_backports/imshow.hpp>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qglv {
namespace opencv {

/*****************************************************************************
** Implementation
*****************************************************************************/

std::pair<cv::Mat, QImage> matToQImage(const cv::Mat &inMat)
{
  switch (inMat.type())
  {
    // 8-bit, 4 channel
    case CV_8UC4:
    {
      QImage image(inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB32);

      return std::pair<cv::Mat, QImage>(inMat, image);
    }

      // 8-bit, 3 channel
    case CV_8UC3:
    {
      QImage image(inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB888);

      return std::pair<cv::Mat, QImage>(inMat, image.rgbSwapped());
    }

      // 8-bit, 1 channel
    case CV_8UC1:
    {
      static QVector<QRgb> sColorTable;

      // only create our color table once
      if (sColorTable.isEmpty())
      {
        for (int i = 0; i < 256; ++i)
          sColorTable.push_back(qRgb(i, i, i));
      }

      QImage image(inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_Indexed8);

      image.setColorTable(sColorTable);

      return std::pair<cv::Mat, QImage>(inMat, image);
    }

    case CV_16UC1:  // typically a depth image, convert to 8UC1 and normalize it
    {
      // no idea how to put a 16bit grayscale into a qimage - thre doesn't seem to be a
      // type for that.
      cv::Mat downsized_image;

      // normalise
      double min;
      double max;
      cv::minMaxIdx(inMat, &min, &max);
      inMat.convertTo(downsized_image, CV_8UC1, 255/(max-min), -min);

      static QVector<QRgb> sColorTable;

      // only create our color table once
      if (sColorTable.isEmpty())
      {
        for (int i = 0; i < 256; ++i)
          sColorTable.push_back(qRgb(i, i, i));
      }

      QImage image(downsized_image.data, downsized_image.cols, downsized_image.rows, downsized_image.step, QImage::Format_Indexed8);

      image.setColorTable(sColorTable);

      return std::pair<cv::Mat, QImage>(downsized_image, image);
    }

    default:
      qWarning() << "qglv::cv::matToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
      break;
  }

  return std::pair<cv::Mat, QImage>(cv::Mat(), QImage());
}

std::pair<cv::Mat, QPixmap> matToQPixmap(const cv::Mat &inMat)
{
  std::pair<cv::Mat, QImage> pair = matToQImage(inMat);
  return std::pair<cv::Mat, QPixmap>(pair.first, QPixmap::fromImage(pair.second));
}

} // namespace cv
} // namespace qglv
