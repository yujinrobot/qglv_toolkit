##############################################################################
# Qt Source Generation
##############################################################################

QT4_WRAP_CPP(MOC_SOURCES ${PROJECT_SOURCE_DIR}/include/qglv/gallery.hpp)
QT4_WRAP_UI(UI_INTERFACE_SOURCES ${PROJECT_SOURCE_DIR}/ui/gallery_interface.ui)
include_directories(${CMAKE_CURRENT_BINARY_DIR})  # this is where ui headers are dropped.

##############################################################################
# Macros
##############################################################################

macro(${PROJECT_NAME}_add_demo name)
  set(target_name ${PROJECT_NAME}_${name})  # unique target names
  add_executable(${target_name} ${name}.cpp ${MOC_SOURCES} ${ARGN})
  set_target_properties(${target_name} PROPERTIES OUTPUT_NAME ${name})
  target_link_libraries(${target_name}
      ${QGLViewer_LIBRARY}
      ${QT_LIBRARIES}
      ${GLUT_LIBRARY}
      ${OPENGL_LIBRARY}
      ${catkin_LIBRARIES}
    )
  # install rule only valid if it is not EXCLUDE_FROM_ALL above.
  install(TARGETS ${target_name} RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
endmacro()

##############################################################################
# Executables
##############################################################################

qglv_gallery_add_demo(background_image)
qglv_gallery_add_demo(frame_transform)
qglv_gallery_add_demo(interface ${UI_INTERFACE_SOURCES})
qglv_gallery_add_demo(keyframe_interpolation)
qglv_gallery_add_demo(manipulated_frame)
qglv_gallery_add_demo(multi_view)
qglv_gallery_add_demo(thumbnail)

