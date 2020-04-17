cmake_minimum_required(VERSION 3.10)

# Set the project name
project(video-app)

# C++17
set(CMAKE_CXX_STANDARD 17)

# Build
include_directories(${PROJECT_SOURCE_DIR})
add_executable(video-app main.cpp Video.cpp)
