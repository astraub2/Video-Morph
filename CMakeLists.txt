cmake_minimum_required(VERSION 2.8.12)

project(warp_serial)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(warp_serial warp_serial.cpp)
target_link_libraries(warp_serial ${OpenCV_LIBS})