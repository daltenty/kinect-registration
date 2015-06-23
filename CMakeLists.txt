cmake_minimum_required(VERSION 3.2)
project(registrationdump)
include(/usr/share/libfreenect/libfreenectConfig.cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories(FREENECT_INCLUDE_DIRS)
add_executable(registrationdump main.cpp)

target_link_libraries(registrationdump freenect)
add_executable(registrationfix fix.h fix.cpp)

target_link_libraries(registrationfix freenect)