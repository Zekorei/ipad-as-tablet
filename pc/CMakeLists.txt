cmake_minimum_required(VERSION 3.16)

project(IpadInputSystemPC VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILE_COMMANDS ON)

# Dependencies
include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.0
)

FetchContent_MakeAvailable(Catch2)

# Core library
add_library(ipad_input_pc_core
    src/mapper.cpp
    src/input.cpp
)

target_include_directories(ipad_input_pc_core 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../shared    
)

# Executable target
add_executable(ipad_input_pc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

target_link_libraries(ipad_input_pc PRIVATE ipad_input_pc_core)

if (WIN32)
    target_link_libraries(ipad_input_pc PRIVATE ws2_32)
endif()

# Tests
enable_testing()

add_executable(ipad_input_pc_tests
    tests/test_mapper.cpp
)

target_link_libraries(ipad_input_pc_tests 
    PRIVATE 
        ipad_input_pc_core
        Catch2::Catch2WithMain
)

add_test(NAME IpadInputSystemTests COMMAND ipad_input_pc_tests)

# Compiler warnings
function(enable_warnings target)
    if (MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endfunction()

enable_warnings(ipad_input_pc_core)
enable_warnings(ipad_input_pc)
enable_warnings(ipad_input_pc_tests)
