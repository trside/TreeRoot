workspace "TreeRoot"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

    startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "TreeRoot/vendor/GLFW/include"

include "TreeRoot/vendor/GLFW"

project "TreeRoot"
    location "TreeRoot"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "trpch.h"
    pchsource "TreeRoot/src/trpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/src",
        "%{IncludeDir.GLFW}"
    }

    links
    {
        "GLFW",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "_CRT_SECURE_NO_WARNINGS",
            "TR_BUILD_DLL",
            "TR_PLATFORM_WINDOWS"
        }

        postbuildcommands
        {
            ("{COPYDIR} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines
        {
            "TR_DEBUG",
            "TR_ENABLE_ASSERT"
        }
        symbols "On"

    filter "configurations:Release"
        defines "TR_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "TR_DIST"
        optimize "On"
        
project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "TreeRoot/vendor/spdlog/include",
        "TreeRoot/src"
    }

    links
    {
        "TreeRoot"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "_CRT_SECURE_NO_WARNINGS",
            "TR_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "TR_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "TR_RELEASE"
        optimize "Speed"

    filter "configurations:Dist"
        defines "TR_DIST"
        optimize "Speed"