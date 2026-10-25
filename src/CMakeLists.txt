add_library(DRAWING_SRC OBJECT
    affine_set_draw.cpp
    box_draw.cpp
    curve_draw.cpp
    drawer.cpp
    drawer_manager.cpp
    drawing_command_line_interface.cpp
    figure_draw.cpp
    function_set_draw.cpp
    grid_paving_draw.cpp
)
target_link_libraries(DRAWING_SRC PRIVATE drawing)
