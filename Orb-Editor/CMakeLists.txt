project(Orb-Editor LANGUAGES CXX) 

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")

# Create executable
add_executable(Orb-Editor ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(Orb-Editor PRIVATE
    "${CMAKE_SOURCE_DIR}/Rune-Engine/src"
    "${CMAKE_SOURCE_DIR}/Rune-Engine/thirdparty/"
)

# Link dependencies
target_link_libraries(Orb-Editor PRIVATE Rune-Engine)

# Platform-specific settings
if(WIN32)
    target_compile_definitions(Orb-Editor PRIVATE RUNE_PLATFORM_WINDOWS)
    target_compile_options(Orb-Editor PRIVATE /Wall)
endif()

# Configuration-specific preprocessor definitions
target_compile_definitions(Orb-Editor PRIVATE
    $<$<CONFIG:Debug>:RUNE_DEBUG>
    $<$<CONFIG:Release>:RUNE_RELEASE>
    $<$<CONFIG:Dist>:RUNE_DIST>
)

# Set MSVC runtime to dynamic:
if(MSVC)
    set_target_properties(Orb-Editor PROPERTIES
        MSVC_RUNTIME_LIBRARY $<$<CONFIG:Debug>:MultiThreadedDebugDLL>$<$<NOT:$<CONFIG:Debug>>:MultiThreadedDLL>
    )
endif()

set_target_outputs(Orb-Editor)
