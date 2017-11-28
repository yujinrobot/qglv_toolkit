##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 2.8.3)
project(qglv_opencv)

##############################################################################
# Find Packages
##############################################################################

find_package(catkin
    REQUIRED
    COMPONENTS
        cmake_modules
        ecl_build
        ecl_command_line
    )

find_package(OpenCV 2 REQUIRED)

find_package(Qt5 QUIET COMPONENTS 
  Core 
  Widgets)

if (Qt5_FOUND)
  set(QT_INCLUDES 
    ${Qt5Core_INCLUDE_DIRS} 
    ${Qt5Widgets_INCLUDE_DIRS})
  set(QT_LIBRARIES 
    Qt5::Core 
    Qt5::Widgets)
  add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0)
else()
  set(QT_INCLUDE_DIRS_NO_SYSTEM TRUE)
  find_package(Qt4 COMPONENTS QtCore QtGui REQUIRED)
  include(${QT_USE_FILE})
  set(QT_INCLUDES ${QT_INCLUDE_DIR} ${QT_INCLUDE_DIR}/QtCore ${QT_INCLUDE_DIR}/QtGui)
  set(QT_LIBRARIES ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
endif()

##############################################################################
# Catkin
##############################################################################

# Because it does not set an xxxx_INCLUDE_DIRS...
# Note : do not use QT_INCLUDE_DIR - that is only /usr/include/qt4 whereas
#        QT_INCLUDES brings in all the required components
set(QT_INCLUDE_DIRS ${QT_INCLUDES})

catkin_package(
    INCLUDE_DIRS include
    LIBRARIES ${PROJECT_NAME}
    CATKIN_DEPENDS
        ecl_command_line
    DEPENDS
        OpenCV
    )

##############################################################################
# Project Configuration
##############################################################################

ecl_enable_cxx11_compiler()
add_definitions(${catkin_DEFINITIONS})
include_directories(
    include
    ${catkin_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
    ${QT_INCLUDES}    # list of escaped QtCore, ... subdirs.
    ${QT_INCLUDE_DIR} # the root level qt4 dir
)

##############################################################################
# Sources
##############################################################################

add_subdirectory(include)
add_subdirectory(src)

##############################################################################
# Installs
##############################################################################

install(DIRECTORY resources DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
