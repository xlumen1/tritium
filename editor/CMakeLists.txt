project(TritiumEditor LANGUAGES CXX)

add_executable(tritium_editor
    src/main.cpp
)

target_link_libraries(tritium_editor PRIVATE tritium)

target_compile_definitions(tritium_editor PRIVATE TRITIUM_EDITOR)

set_target_properties(tritium_editor PROPERTIES
    OUTPUT_NAME "TritiumEditor"
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
