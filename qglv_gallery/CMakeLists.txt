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
find_path(QGLViewer_INCLUDE_DIRS QGLViewer/qglviewer.h)
find_library(QGLViewer_LIBRARY NAMES QGLViewer)
# Since we have no cmake module, for QGLViewer, we must fetch qt ourselves.
set(QT_INCLUDE_DIRS_NO_SYSTEM TRUE)
find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL REQUIRED)
include(${QT_USE_FILE})

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

add_subdirectory(src)

##############################################################################
# Installs
##############################################################################

install(DIRECTORY ui DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
