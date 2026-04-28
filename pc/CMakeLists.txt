cmake_minimum_required(VERSION 3.16)
project(IpadInputSystemPC VERSION 0.1 LANGUAGES CXX)

option(ENABLE_TESTS "Build tests" OFF)

# Set default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Add cmake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Include configuration modules
include(cmake/Compiler.cmake)
include(cmake/Dependencies.cmake)

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add subdirectories
add_subdirectory(src)

if(ENABLE_TESTS)
    add_subdirectory(tests)
endif()
