project(Rune-Engine LANGUAGES C CXX)

# Add third-party dependencies

add_subdirectory(thirdparty/GLFW)



# Create GLAD target

file(GLOB GLAD_SOURCES "thirdparty/glad/src/*.c")
add_library(glad STATIC ${GLAD_SOURCES})
target_include_directories(glad PUBLIC 

    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad/include"
)

if(WIN32)
    target_link_libraries(glad PRIVATE opengl32)

endif()

# Create ImGui target
file(GLOB IMGUI_SOURCES
    "thirdparty/imgui/*.cpp"
    "thirdparty/imgui/backends/imgui_impl_glfw.cpp"
    "thirdparty/imgui/backends/imgui_impl_opengl3.cpp"
)

add_library(imgui STATIC ${IMGUI_SOURCES})

target_include_directories(imgui PUBLIC

    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/imgui"

    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/GLFW/include"

    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad/include"

)
target_compile_definitions(imgui PRIVATE IMGUI_IMPL_OPENGL_LOADER_GLAD)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")

# Create shared library
add_library(Rune-Engine SHARED ${SOURCES} ${HEADERS})

# Precompiled headers
target_precompile_headers(Rune-Engine PRIVATE src/rune_pch.h)

# Include directories

target_include_directories(Rune-Engine PUBLIC
    "src"
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/spdlog/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/GLFW/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad/include"
)

# Link dependencies
target_link_libraries(Rune-Engine PRIVATE 
    glfw
    glad
    imgui  # Link ImGui

)

# Platform-specific settings
if(WIN32)
    target_compile_definitions(Rune-Engine PRIVATE 
        RUNE_PLATFORM_WINDOWS 
        RUNE_BUILD_DLL
        GLFW_INCLUDE_NONE
    )

    target_compile_options(Rune-Engine PRIVATE /Wall)

    target_link_libraries(Rune-Engine PRIVATE 
        opengl32 
        gdi32 
        user32 
        shell32
    )

endif()

# Configuration-specific preprocessor definitions

target_compile_definitions(Rune-Engine PRIVATE
    $<$<CONFIG:Debug>:RUNE_DEBUG>
    $<$<CONFIG:Release>:RUNE_RELEASE>
    $<$<CONFIG:Dist>:RUNE_DIST>

)



# Set MSVC runtime to dynamic

if(MSVC)
    set_target_properties(Rune-Engine PROPERTIES
        MSVC_RUNTIME_LIBRARY $<$<CONFIG:Debug>:MultiThreadedDebugDLL>$<$<NOT:$<CONFIG:Debug>>:MultiThreadedDLL>
    )

endif()



# Post-build command to copy DLL to Sandbox output directory

add_custom_command(TARGET Rune-Engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Rune-Engine>
        "${CMAKE_SOURCE_DIR}/bin/${CMAKE_CFG_INTDIR}-${CMAKE_SYSTEM_NAME}-${ARCHITECTURE}/Sandbox"

)



set_target_outputs(Rune-Engine)