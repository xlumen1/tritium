project(TritiumEngine LANGUAGES CXX)

set(ENGINE_SOURCES
    src/Engine.cpp
)

set(ENGINE_HEADERS
    include/tritium/api.hpp
    include/tritium/Engine.hpp
)

if(TRITIUM_BUILD_SHARED)
    add_library(tritium SHARED ${ENGINE_SOURCES} ${ENGINE_HEADERS})
    target_compile_definitions(tritium PRIVATE TRITIUM_BUILD_DLL)
else()
    add_library(tritium STATIC ${ENGINE_SOURCES} ${ENGINE_HEADERS})
endif()

target_include_directories(tritium PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(tritium PUBLIC ${TRITIUM_DEPS})

if(WIN32)
    target_compile_definitions(tritium PUBLIC TRITIUM_PLATFORM_WINDOWS)
elseif(UNIX)
    target_compile_definitions(tritium PUBLIC TRITIUM_PLATFORM_LINUX)
endif()

set_target_properties(tritium PROPERTIES
    OUTPUT_NAME "tritium"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}"
)
