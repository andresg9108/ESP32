# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)

set(EXTRA_COMPONENT_DIRS 
    ${CMAKE_SOURCE_DIR}/node_modules/ag-util-esp32/wifi
    ${CMAKE_SOURCE_DIR}/node_modules/ag-util-esp32/httpServer)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(switchOnLEDWithAPI)
