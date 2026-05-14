target_include_directories(ipad_input_pc_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(config)
add_subdirectory(input)
add_subdirectory(math)
add_subdirectory(output)
add_subdirectory(types)
