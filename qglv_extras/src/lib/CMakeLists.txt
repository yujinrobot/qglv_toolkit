##############################################################################
# Sources
##############################################################################

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

##############################################################################
# Moc Sources
##############################################################################

qt4_wrap_cpp(MOC_SOURCES

    ${PROJECT_SOURCE_DIR}/include/qglv/objects/fat_man.hpp
    ${PROJECT_SOURCE_DIR}/include/qglv/objects/teleport_arrow.hpp

    ${PROJECT_SOURCE_DIR}/include/qglv/widgets/qgl_viewer.hpp
)

##############################################################################
# Library
##############################################################################

add_library(${PROJECT_NAME} ${SOURCES} ${MOC_SOURCES})

target_link_libraries(${PROJECT_NAME}
    ${catkin_LIBRARIES}
    ${OPENGL_LIBRARY}
    ${QT_LIBRARIES}
    ${QGLViewer_LIBRARY}
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

