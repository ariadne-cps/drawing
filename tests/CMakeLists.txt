include(CTest)

set(UNIT_TESTS
    test_drawer
    test_drawing_command_line_interface
    test_point_draw
    test_box_draw
    test_paving_draw
    test_figure_drawing
    geometry_test_affine_sets
    geometry_test_constrained_image_set
    geometry_test_constraint_set
    geometry_test_curve
    geometry_test_paving
    geometry_test_grid_paving_extensions
    geometry_test_validated_constrained_image_set
)
foreach(TEST ${UNIT_TESTS})
    add_executable(${TEST} ${TEST}.cpp)
    target_link_libraries(${TEST} ariadne-drawing drawing)
    add_test(NAME ${TEST} COMMAND $<TARGET_FILE:${TEST}>)
    set_property(TEST ${TEST} PROPERTY LABELS "drawing")
endforeach()
add_custom_target(tests)
add_dependencies(tests ${UNIT_TESTS})
