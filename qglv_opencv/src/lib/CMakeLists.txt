##############################################################################
# Qt
##############################################################################

qt4_wrap_cpp(
    MOC_SOURCES
        ${PROJECT_SOURCE_DIR}/include/qglv/widgets/cv_image_view.hpp
)

qt4_add_resources(
    UI_IMAGE_RESOURCES
        ${PROJECT_SOURCE_DIR}/resources/images/images.qrc
)

##############################################################################
# Sources
##############################################################################

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

##############################################################################
# Library
##############################################################################

add_library(
    ${PROJECT_NAME}
        ${SOURCES}
        ${MOC_SOURCES}
        ${UI_IMAGE_RESOURCES}
)

target_link_libraries(${PROJECT_NAME}
    ${catkin_LIBRARIES}
    ${QT_LIBRARIES}
    ${OpenCV_LIBRARIES}
)

##############################################################################
# Installs
##############################################################################
 
install(TARGETS ${PROJECT_NAME}
   RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)
