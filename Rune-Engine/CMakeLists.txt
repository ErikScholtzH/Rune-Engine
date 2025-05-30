cmake_minimum_required(VERSION 3.15)
project(Rune-Engine LANGUAGES C CXX)

# Configuration options --------------------------------------------------------
set(ARCHITECTURE "x64")  # Explicitly set architecture for output directory

# Third-party dependencies -----------------------------------------------------
add_subdirectory(thirdparty/GLFW)

# GLAD target ------------------------------------------------------------------
file(GLOB GLAD_SOURCES "thirdparty/glad/src/*.c")
add_library(glad STATIC ${GLAD_SOURCES})
target_include_directories(glad PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad/include"
)

if(WIN32)
    target_link_libraries(glad PRIVATE opengl32)
endif()

# ImGui target -----------------------------------------------------------------
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

# stb_image target -------------------------------------------------------------
file(GLOB STB_IMAGE_SOURCES "thirdparty/stb_image/stb_image.cpp")
add_library(stb_image STATIC ${STB_IMAGE_SOURCES})
target_include_directories(stb_image PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/stb_image"
)

# Main engine library ----------------------------------------------------------
# Note: Consider explicitly listing source files instead of GLOB
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")

add_library(Rune-Engine STATIC ${SOURCES} ${HEADERS})
target_precompile_headers(Rune-Engine PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/rune_pch.h")

# Include directories ----------------------------------------------------------
target_include_directories(Rune-Engine PUBLIC
    "src"
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/spdlog/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/GLFW/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glm"  # GLM is header-only
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/imgui"
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/stb_image"
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>
)

# Dependencies -----------------------------------------------------------------
target_link_libraries(Rune-Engine PRIVATE 
    glfw
    glad
    imgui
    stb_image
)

# Platform-specific configuration ----------------------------------------------
if(WIN32)
    target_compile_definitions(Rune-Engine PRIVATE 
        RUNE_PLATFORM_WINDOWS 
        RUNE_BUILD_DLL
        GLFW_INCLUDE_NONE
        RUNE_ENABLE_ASSERTS
        RUNE_ENABLE_PROFILING
    )

    target_compile_options(Rune-Engine PRIVATE /Wall)

    target_link_libraries(Rune-Engine PRIVATE 
        opengl32 
        gdi32 
        user32 
        shell32
    )
endif()

# Configurations ---------------------------------------------------------------
target_compile_definitions(Rune-Engine PRIVATE
    $<$<CONFIG:Debug>:RUNE_DEBUG>
    $<$<CONFIG:Release>:RUNE_RELEASE>
    $<$<CONFIG:Dist>:RUNE_DIST>
)

# MSVC runtime configuration ---------------------------------------------------
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
    set_target_properties(Rune-Engine PROPERTIES
        MSVC_RUNTIME_LIBRARY "${CMAKE_MSVC_RUNTIME_LIBRARY}"
    )
endif()