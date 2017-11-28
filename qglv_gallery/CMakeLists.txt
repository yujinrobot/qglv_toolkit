##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 2.8.3)
project(qglv_gallery)

##############################################################################
# Find Packages
##############################################################################

find_package(catkin
    REQUIRED
    COMPONENTS
    )

find_package(OpenGL REQUIRED)

# TODO: put this logic in a cmake find module - repeated in qglv_extras
find_path(QGLViewer_INCLUDE_DIRS QGLViewer/qglviewer.h)
find_library(QGLViewer_LIBRARY NAMES QGLViewer)
# Since we have no cmake module, for QGLViewer, we must fetch qt ourselves.
set(QT_INCLUDE_DIRS_NO_SYSTEM TRUE)
if(QGLViewer_INCLUDE_DIRS)
  set(QGLViewer_VERSION_FILE ${QGLViewer_INCLUDE_DIRS}/QGLViewer/config.h)
  file(READ ${QGLViewer_VERSION_FILE} QGLViewer_VERSION_FILE_CONTENTS)
  string(REGEX MATCH "#define QGLVIEWER_VERSION 0x[0-9]+" QGLViewer_VERSION "${QGLViewer_VERSION_FILE_CONTENTS}")
  string(REGEX REPLACE "#define QGLVIEWER_VERSION 0x0([0-9]+)" "\\1" QGLViewer_VERSION "${QGLViewer_VERSION}")
  message(STATUS "QGLViewer_VERSION..........${QGLViewer_VERSION}")
endif()

find_package(Qt5 QUIET COMPONENTS 
  Core 
  Widgets 
  Xml 
  OpenGL)

if (Qt5_FOUND)
  set(QT_INCLUDES 
    ${Qt5Core_INCLUDE_DIRS} 
    ${Qt5Widgets_INCLUDE_DIRS} 
    ${Qt5Xml_INCLUDE_DIRS} 
    ${Qt5OpenGL_INCLUDE_DIRS})
  set(QT_LIBRARIES 
    Qt5::Core 
    Qt5::Widgets 
    Qt5::Xml 
    Qt5::OpenGL)
  add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0)
else()
  find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL REQUIRED)
  include(${QT_USE_FILE})
  set(QT_INCLUDES ${QT_INCLUDE_DIR} ${QT_INCLUDE_DIR}/QtCore ${QT_INCLUDE_DIR}/QtGui ${QT_INCLUDE_DIR}/QtOpenGL)
  set(QT_LIBRARIES ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTOPENGL_LIBRARY})
endif()

# be nice to get rid of this as we only use it for two things - 1) text
# rendering and 2) libqglviewer doesn't directly depend on it, but
# including some of the example program apis brings in this
# requirement...
find_package(GLUT REQUIRED)

##############################################################################
# Catkin
##############################################################################

# only applications, no exports necessary
catkin_package()

##############################################################################
# Project Configuration
##############################################################################

add_definitions(${catkin_DEFINITIONS})
include_directories(
    include
    ${QGLViewer_INCLUDE_DIRS}
    ${QT_INCLUDES}    # list of escaped QtCore, ... subdirs.
    ${QT_INCLUDE_DIR} # the root level qt4 dir
    ${GLUT_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
    ${catkin_INCLUDE_DIRS}
)

##############################################################################
# Sources
##############################################################################

# ubuntu saucy has 203xx versions, make sure to avoid building them as
# we currently do not support (trusty has 205xx)
if(${QGLViewer_VERSION} GREATER "20399")
  add_subdirectory(src)
endif()

##############################################################################
# Installs
##############################################################################

install(DIRECTORY ui DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
