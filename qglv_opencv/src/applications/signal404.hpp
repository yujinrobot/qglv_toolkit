/**
 * @file /qglv_opencv/include/qglv/demos/signal404.hpp
 */
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef qglv_opencv_DEMOS_SIGNAL404_HPP_
#define qglv_opencv_DEMOS_SIGNAL404_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QApplication>
#include <QObject>
#include <QThread>
#include <QTime>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

/*****************************************************************************
** Classes
*****************************************************************************/

class Signal404 : public QThread {
  Q_OBJECT

public:
  Signal404(const std::string& filename) : filename(filename) {}
  virtual ~Signal404() {}

signals:
  void triggerImage(cv::Mat);
  void trigger404Image();

protected:
  void run() {
    for ( unsigned int i = 5; i > 0; --i) {
      std::cout << "Looping " << i << std::endl;
      QTime dieTime = QTime::currentTime().addSecs( 1 );
      while( QTime::currentTime() < dieTime )
      {
          QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
      }
    }
    if (!filename.empty() ) {
      cv::Mat image;
      image = cv::imread(filename, CV_LOAD_IMAGE_COLOR);
      emit triggerImage(image);
    } else {
      emit trigger404Image();
    }
  }
  const std::string& filename;
};

#endif /* qglv_opencv_DEMOS_SIGNAL404_HPP_ */
