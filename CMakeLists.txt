cmake_minimum_required(VERSION 3.8)
project(qvtkplugin)

find_package(Qt5 COMPONENTS Widgets UiPlugin REQUIRED)
find_package(VTK REQUIRED)

# Ensure Qt MOC is enabled
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_library(qvtkplugin SHARED qvtkplugin.cpp)

target_link_libraries(qvtkplugin
    Qt5::Widgets
    Qt5::UiPlugin
    ${VTK_LIBRARIES}
)

install(TARGETS qvtkplugin
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/qtcreator/plugins
)

