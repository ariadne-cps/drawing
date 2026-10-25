cmake_minimum_required(VERSION 3.15)

project(Drawing VERSION 1.0)

option(WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)
option(BUILD_PYTHON_BINDINGS "Build Python bindings" ON)

if(NOT TARGET ariadne-configuration)
    find_package(Git REQUIRED)
    execute_process(COMMAND "${GIT_EXECUTABLE}" -C "${CMAKE_CURRENT_SOURCE_DIR}"
                    submodule update --init -- ss/configuration
                    RESULT_VARIABLE _result)
    if(_result)
        message(FATAL_ERROR "Cannot initialize configuration submodule")
    endif()
    include("${CMAKE_CURRENT_SOURCE_DIR}/ss/configuration/cmake/ProjectOptions.cmake")
endif()

if(EXISTS "${PROJECT_SOURCE_DIR}/.git")
    require_same_dependency_commit(Configuration
        CHAINS
            "configuration"
            "kernel|configuration"
            "rendering|configuration"
    )
endif()

setup_project()

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(ss)

add_library(drawing INTERFACE)
target_include_directories(drawing INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/ariadne-drawing>
)
target_link_libraries(drawing INTERFACE kernel rendering)

add_subdirectory(src)
target_link_libraries(DRAWING_SRC PRIVATE drawing)

ariadne_register_public_headers(
    TARGET drawing
    DIRECTORIES "${PROJECT_SOURCE_DIR}/include/drawing"
    FILES "${PROJECT_SOURCE_DIR}/include/ariadne-drawing.hpp"
)

setup_project_library(
    TARGET ariadne-drawing
    OBJECTS DRAWING_SRC
    LINK_LIBRARIES drawing
)

setup_standalone_project_tests(
    TARGET ariadne-drawing
    TEST_DIRECTORY tests
    TEST_TARGET tests
    SOURCES
        "${PROJECT_SOURCE_DIR}/include"
        "${PROJECT_SOURCE_DIR}/src"
)

if(BUILD_PYTHON_BINDINGS)
    add_subdirectory(python)
endif()

if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    ariadne_install_dependency_bundle(
        TARGET drawing
        DESTINATION include/ariadne-drawing
    )
endif()
