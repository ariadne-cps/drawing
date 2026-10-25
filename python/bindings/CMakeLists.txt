include_directories(${Python3_INCLUDE_DIRS})
get_target_property(PYTHON_COMMON_SOURCE_DIR pyariadne-python-common SOURCE_DIR)

add_library(pyariadne-drawing-submodule-obj OBJECT drawing_submodule.cpp)
target_include_directories(pyariadne-drawing-submodule-obj PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${PYTHON_COMMON_SOURCE_DIR}/include"
    $<TARGET_PROPERTY:pyariadne-kernel,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:pyariadne-rendering,INTERFACE_INCLUDE_DIRECTORIES>
)
target_link_libraries(pyariadne-drawing-submodule-obj PRIVATE
    pyariadne-python-common pybind11::module drawing
)
set_target_properties(pyariadne-drawing-submodule-obj PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_library(pyariadne-drawing INTERFACE)
target_sources(pyariadne-drawing INTERFACE
    $<TARGET_OBJECTS:pyariadne-drawing-submodule-obj>
)
target_include_directories(pyariadne-drawing INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<TARGET_PROPERTY:pyariadne-kernel,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:pyariadne-rendering,INTERFACE_INCLUDE_DIRECTORIES>
)
target_link_libraries(pyariadne-drawing INTERFACE
    pyariadne-kernel pyariadne-rendering
)

ariadne_add_python_module(NAME drawing MODULE_SOURCE drawing_module.cpp)
