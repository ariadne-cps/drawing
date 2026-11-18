include(CTest)

set(UNIT_TESTS
    test_drawer
    test_drawing_command_line_interface
    test_point_draw
    test_box_draw
    test_paving_draw
    test_augmented_paving_draw
    test_figure_drawing
    test_validated_constrained_image_set_draw
    test_binary_tree_paving_draw
    test_curve_draw
    test_constraint_set_draw
    test_constrained_image_set_draw
    test_affine_set_draw
    test_spre22_critical_draw
)
foreach(TEST ${UNIT_TESTS})
    add_executable(${TEST} ${TEST}.cpp)
    target_link_libraries(${TEST} PRIVATE ariadne-drawing drawing ariadne-testing)
    add_test(NAME ${TEST} COMMAND $<TARGET_FILE:${TEST}> --concise --logtonull)
    set_property(TEST ${TEST} PROPERTY LABELS "drawing")
endforeach()
add_custom_target(tests)
add_dependencies(tests ${UNIT_TESTS})

# An original SPRE22 enclosure used to stall the old affine boundary walk.
set_tests_properties(test_spre22_critical_draw PROPERTIES TIMEOUT 120)
