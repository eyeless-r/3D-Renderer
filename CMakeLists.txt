cmake_minimum_required(VERSION 3.27)
project(3D-Renderer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(submodules/eigen)
include_directories(submodules/eigen/)

add_subdirectory(submodules/SFML)
include_directories(submodules/SFML/include)

set(SRC_DIR src)
file(GLOB SRC_FILES "${SRC_DIR}/*.cpp")

add_executable(3D-Renderer main.cpp ${SRC_FILES})

target_link_libraries(3D-Renderer PRIVATE Eigen3::Eigen SFML::Graphics SFML::Window)
