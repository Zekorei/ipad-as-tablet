# Test configuration

# Enable testing
enable_testing()

# Test executable
add_executable(ipad_input_pc_tests 
    test_math_vec2.cpp

    test_pipeline_input_pipeline.cpp

    test_pipeline_stages_aspect.cpp
    test_pipeline_stages_clamp.cpp
    test_pipeline_stages_display.cpp
    test_pipeline_stages_subregion.cpp
)

# Add testing utilities
target_include_directories(ipad_input_pc_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/utils
)

target_link_libraries(ipad_input_pc_tests 
    PRIVATE 
        ipad_input_pc_core
        Catch2::Catch2WithMain
)

enable_warnings(ipad_input_pc_tests)

# Register test
add_test(NAME IpadInputSystemTests COMMAND ipad_input_pc_tests)

# Custom run target
add_custom_target(run_tests
    COMMAND ${CMAKE_BINARY_DIR}/bin/ipad_input_pc_tests
    DEPENDS ipad_input_pc_tests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
