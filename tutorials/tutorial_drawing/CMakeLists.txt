cmake_minimum_required(VERSION 3.15)
project(AriadneDrawingTutorial LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
find_package(AriadneDrawing REQUIRED)

add_executable(tutorial_drawing tutorial_drawing.cpp)
target_link_libraries(tutorial_drawing PRIVATE AriadneDrawing::ariadne-drawing)
