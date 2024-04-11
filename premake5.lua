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
IncludeDir["Glad"] = "TreeRoot/vendor/Glad/include"

include "TreeRoot/vendor/GLFW"
include "TreeRoot/vendor/Glad"

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
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}"
    }

    links
    {
        "GLFW",
        "Glad",
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
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "TR_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "TR_DIST"
        buildoptions "/MD"
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
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "TR_RELEASE"
        buildoptions "/MD"
        optimize "Speed"

    filter "configurations:Dist"
        defines "TR_DIST"
        buildoptions "/MD"
        optimize "Speed"