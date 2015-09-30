/**
 * @file /dslam_viewer/src/applications/map_viewer.cpp
 * 
 * @brief Short description of this file.
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <ecl/command_line/cmd_line.hpp>
#include <ecl/command_line/unlabeled_value_arg.hpp>
#include <iostream>
#include <QApplication>
#include <QObject>
#include "../../include/qglv/widgets/cv_image_view.hpp"
#include "signal404.hpp"

/*****************************************************************************
 ** Methods
 *****************************************************************************/

std::string parse_arguments(int argc, char** argv) {
  ecl::CmdLine cmd("Demos the cv to qt graphics view widget.");
  ecl::UnlabeledValueArg<std::string> filename_arg("filename", "filename of the image to load", false, "", "string", cmd);
  cmd.parse(argc, argv);
  return filename_arg.getValue();
}

/*****************************************************************************
** Main
*****************************************************************************/

int main(int argc, char** argv)
{
  std::string filename = parse_arguments(argc, argv);

  /****************************************
   ** Qt
   ****************************************/
  QApplication application(argc,argv);
  Signal404 signal404(filename);
  qglv::CvImageView image_view;
  QObject::connect(&signal404, SIGNAL(trigger404Image()),
                   &image_view, SLOT(show404Image()));
  QObject::connect(&signal404, SIGNAL(triggerImage(cv::Mat)),
                   &image_view, SLOT(showImage(cv::Mat)));
  signal404.start();
  image_view.show();
  return application.exec();
}
