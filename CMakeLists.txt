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

get_filename_component(SDL3_ROOT "${SDL3_DIR}" DIRECTORY)
set(SDL3_DLL "${SDL3_ROOT}/bin/SDL3.dll" CACHE FILEPATH "Path to SDL3 runtime DLL")

set(TRITIUM_DEPS Vulkan::Vulkan SDL3::SDL3 CACHE INTERNAL "Tritium dependencies")

include(FetchContent)

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG docking
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(imgui)
if(EXISTS "${imgui_SOURCE_DIR}/.git")
    file(REMOVE_RECURSE "${imgui_SOURCE_DIR}/.git")
endif()

set(IMGUI_INCLUDE_DIRS
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
    CACHE INTERNAL "Dear ImGui include directories"
)

set(IMGUI_BACKENDS
    ${imgui_SOURCE_DIR}/backends/imgui_impl_vulkan.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
    CACHE INTERNAL "Dear ImGui backend sources"
)

set(IMGUI_SOURCES
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer3.cpp
    CACHE INTERNAL "Dear ImGui core + backend sources"
)

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
