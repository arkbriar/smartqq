# Specify the minimum version of Cmake
cmake_minimum_required (VERSION 2.6)

# Project's name
project (smartqq)

# add the executable
add_executable (smartqq main.cpp client.cpp api.cpp model.cpp)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -std=c++11")

add_subdirectory(cpr)
include_directories(${CPR_INCLUDE_DIRS})
target_link_libraries(smartqq ${CPR_LIBRARIES})
