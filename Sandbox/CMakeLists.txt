project(Sandbox LANGUAGES CXX)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")

# Create executable
add_executable(Sandbox ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(Sandbox PRIVATE
    "${CMAKE_SOURCE_DIR}/Rune-Engine/src"
    "${CMAKE_SOURCE_DIR}/Rune-Engine/vendor/spdlog/include"
)

# Link dependencies
target_link_libraries(Sandbox PRIVATE Rune-Engine)

# Platform-specific settings
if(WIN32)
    target_compile_definitions(Sandbox PRIVATE RUNE_PLATFORM_WINDOWS)
    target_compile_options(Sandbox PRIVATE /Wall)
endif()

# Configuration-specific preprocessor definitions
target_compile_definitions(Sandbox PRIVATE
    $<$<CONFIG:Debug>:RUNE_DEBUG>
    $<$<CONFIG:Release>:RUNE_RELEASE>
    $<$<CONFIG:Dist>:RUNE_DIST>
)

# Set MSVC runtime to dynamic:
if(MSVC)
    set_target_properties(Sandbox PROPERTIES
        MSVC_RUNTIME_LIBRARY $<$<CONFIG:Debug>:MultiThreadedDebugDLL>$<$<NOT:$<CONFIG:Debug>>:MultiThreadedDLL>
    )
endif()

set_target_outputs(Sandbox)
