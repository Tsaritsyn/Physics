cmake_minimum_required(VERSION 3.10)
project(Physics)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(Physics main.cpp include.hpp lib/scenes/PixelGrid.cpp include/scenes/PixelGrid.h lib/App.cpp include/App.h lib/scenes/Scene.cpp include/scenes/Scene.h lib/scenes/Camera.cpp include/scenes/Camera.h lib/scenes/Object.cpp include/scenes/Object.h include/scenes.hpp lib/scenes/Ray.cpp include/scenes/Ray.h lib/scenes/Sphere.cpp include/scenes/Sphere.h lib/common.cpp include/common.h lib/scenes/Octree.cpp include/scenes/Octree.h lib/scenes/BBox.cpp include/scenes/BBox.h)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
