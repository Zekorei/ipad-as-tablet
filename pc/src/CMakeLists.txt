# Core library and executable targets

# Core library
add_library(ipad_input_pc_core STATIC)

target_include_directories(ipad_input_pc_core 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../../shared
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

enable_warnings(ipad_input_pc_core)

# Add subdirectories for component sources
add_subdirectory(config)
add_subdirectory(input)
add_subdirectory(math)
add_subdirectory(output)
add_subdirectory(types)

# Main executable
add_executable(ipad_input_pc main.cpp)

target_link_libraries(ipad_input_pc PRIVATE ipad_input_pc_core)

if (WIN32)
    target_link_libraries(ipad_input_pc PRIVATE ws2_32)
endif()

enable_warnings(ipad_input_pc)

# Custom run target
add_custom_target(run_app
    COMMAND ${CMAKE_BINARY_DIR}/bin/ipad_input_pc
    DEPENDS ipad_input_pc
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
