project(TritiumRuntime LANGUAGES CXX)

add_executable(tritium_runtime
    src/main.cpp
)

target_link_libraries(tritium_runtime PRIVATE tritium)

target_compile_definitions(tritium_runtime PRIVATE TRITIUM_RUNTIME)

set_target_properties(tritium_runtime PROPERTIES
    OUTPUT_NAME "TritiumRuntime"
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
