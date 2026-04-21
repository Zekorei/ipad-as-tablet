cmake_minimum_required(VERSION 3.16)

project(IpadInputSystemPC VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCES
    src/main.cpp
    src/network.cpp
    src/input.cpp
    src/protocol.cpp
)

set(HEADERS
    include/network.h
    include/input.h
    include/protocol.h
)

# Executable
add_executable(ipad_input_pc ${SOURCES} ${HEADERS})

# Windows-specific networking libraries
if (WIN32)
    target_link_libraries(ipad_input_pc PRIVATE ws2_32)
endif()

# Include directories
target_include_directories(ipad_input_pc PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Compiler warnings
if (MSVC)
    target_compile_options(ipad_input_pc PRIVATE /W4)
else()
    target_compile_options(ipad_input_pc PRIVATE -Wall -Wextra -Wpedantic)
endif()
