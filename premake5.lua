workspace "Rune-Engine"
    architecture "x64"
    startproject "Sandbox"
    
    configurations {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Rune-Engine"
    location "Rune-Engine"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "rune_pch.h"
    pchsource "Rune-Engine/src/rune_pch.cpp"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "on"
        systemversion "latest"

        defines {
            "RUNE_PLATFORM_WINDOWS",
            "RUNE_BUILD_DLL"
        }

        postbuildcommands {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines { "RUNE_DEBUG" }
        symbols "on"

    filter "configurations:Release"
        defines { "RUNE_RELEASE" }
        optimize "on"

    filter "configurations:Dist"
        defines { "RUNE_DIST" }
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "Rune-Engine/vendor/spdlog/include",
        "Rune-Engine/src"
    }

    links {
        "Rune-Engine"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "on"
        systemversion "latest"

        defines {
            "RUNE_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines { "RUNE_DEBUG" }
        symbols "on"

    filter "configurations:Release"
        defines { "RUNE_RELEASE" }
        optimize "on"

    filter "configurations:Dist"
        defines { "RUNE_DIST" }
        optimize "on"