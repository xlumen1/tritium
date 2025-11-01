cmake_minimum_required(VERSION 3.20)
project(Tritium LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Options
option(TRITIUM_BUILD_SHARED "Build Tritium engine as a shared library" ON)
option(TRITIUM_BUILD_EDITOR "Build Tritium editor" ON)
option(TRITIUM_BUILD_RUNTIME "Build Tritium Runtime" ON)

# Output Dirs
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Deps
find_package(Vulkan REQUIRED)
find_package(SDL3 REQUIRED CONFIG)

set(TRITIUM_DEPS Vulkan::Vulkan SDL3::SDL3 CACHE INTERNAL "Tritium dependencies")

# Compiler Flags
if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Subdirectories
add_subdirectory(engine)

if(TRITIUM_BUILD_RUNTIME)
    add_subdirectory(runtime)
endif()

if(TRITIUM_BUILD_EDITOR)
    add_subdirectory(editor)
endif()
