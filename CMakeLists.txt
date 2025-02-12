cmake_minimum_required(VERSION 3.15)
project(Rune-Engine)

# Set default build type if none specified (for single-configuration generators)
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose build type" FORCE)
endif()

set(ARCHITECTURE "x64")
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Dist" CACHE STRING "Build configurations" FORCE)

# C++ standard and compiler settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Do not set a global runtime property; we'll set MSVC runtime on each target.
#
# Configure output directories
function(set_target_outputs target)
    set(output_dir "bin/${CMAKE_CFG_INTDIR}-${CMAKE_SYSTEM_NAME}-${ARCHITECTURE}/${target}")
    set_target_properties(${target} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/${output_dir}"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/${output_dir}"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/${output_dir}"
    )
endfunction()

add_subdirectory(Rune-Engine)
add_subdirectory(Sandbox)