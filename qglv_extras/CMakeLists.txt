##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 2.8.3)
project(qglv_extras)

##############################################################################
# Find Packages
##############################################################################

find_package(catkin
    REQUIRED
    COMPONENTS
        cmake_modules
        ecl_build
        qglv_opengl
    )

find_package(Eigen REQUIRED)
find_package(OpenGL REQUIRED)
find_package(sophus REQUIRED)

# TODO: put this logic in a cmake find module - repeated in qglv_gallery
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

find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL REQUIRED)
include(${QT_USE_FILE})

##############################################################################
# Catkin
##############################################################################

# Because it does not set an xxxx_INCLUDE_DIRS...
set(OPENGL_INCLUDE_DIRS ${OPENGL_INCLUDE_DIR})
# Note : do not use QT_INCLUDE_DIR - that is only /usr/include/qt4 whereas
#        QT_INCLUDES brings in all the required components
set(QT_INCLUDE_DIRS ${QT_INCLUDES})

# not supporting versions older than that on ubuntu trusty
if(${QGLViewer_VERSION} GREATER "20304")
    catkin_package(
        INCLUDE_DIRS include
        LIBRARIES ${PROJECT_NAME} 
        CATKIN_DEPENDS
            qglv_opengl
        DEPENDS
            Eigen
            OPENGL
            QGLViewer
            QT
            sophus
    )
else()
    catkin_package()
endif()

##############################################################################
# Project Configuration
##############################################################################

ecl_enable_cxx11_compiler()
add_definitions(${catkin_DEFINITIONS})
include_directories(
    include
    ${QGLViewer_INCLUDE_DIRS}
    ${QT_INCLUDES}    # list of escaped QtCore, ... subdirs.
    ${QT_INCLUDE_DIR} # the root level qt4 dir
    ${OPENGL_INCLUDE_DIR}
    ${sophus_INCLUDE_DIRS}
    ${EIGEN_INCLUDE_DIRS}
    ${catkin_INCLUDE_DIRS}
)

##############################################################################
# Sources
##############################################################################

# not supporting versions older than that on ubuntu trusty
if(${QGLViewer_VERSION} GREATER "20304")
    add_subdirectory(include)
    add_subdirectory(src)
endif()

##############################################################################
# Installs
##############################################################################

#install(DIRECTORY launch DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
