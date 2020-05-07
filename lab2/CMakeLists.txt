cmake_minimum_required(VERSION 3.1)

set(OpenCV_DIR ${C//opencv/build})
project(lab2)

find_package(OpenCV REQUIRED)

add_executable(lab2 src/main.cpp)

target_link_libraries(lab2 ${OpenCV_LIBS})
