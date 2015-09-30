##############################################################################
# Qt Applications
##############################################################################

qt4_wrap_cpp(MOC_SOURCES signal404.hpp)
add_executable(demo_cv_image_view cv_image_view.cpp ${MOC_SOURCES})
target_link_libraries(
    demo_cv_image_view
        ${PROJECT_NAME}
)
install(TARGETS demo_cv_image_view RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
