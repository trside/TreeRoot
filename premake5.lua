workspace "TreeRoot"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

    defines
    {
        "_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "TreeRoot/vendor/GLFW/include"
IncludeDir["Glad"] = "TreeRoot/vendor/Glad/include"
IncludeDir["Imgui"] = "TreeRoot/vendor/imgui"
IncludeDir["glm"] = "TreeRoot/vendor/glm/glm"

group "Dependencies"
    include "TreeRoot/vendor"
group ""

project "TreeRoot"
    location "TreeRoot"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "trpch.h"
    pchsource "TreeRoot/src/trpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
    }

    includedirs
    {
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/src",
        "%{prj.name}/vendor",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.Imgui}",
        "%{IncludeDir.glm}"
    }

    links
    {
        "GLFW",
        "Glad",
        "opengl32.lib",
        "Imgui"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "TR_BUILD_DLL",
            "TR_PLATFORM_WINDOWS"
        }

        postbuildcommands
        {
            ("{COPYDIR} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
        }

    filter "configurations:Debug"
        defines "TR_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "TR_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "TR_DIST"
        runtime "Release"
        optimize "On"
        
project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

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
        systemversion "latest"

        defines
        {
            "_CRT_SECURE_NO_WARNINGS",
            "TR_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "TR_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "TR_RELEASE"
        runtime "Release"
        optimize "Speed"

    filter "configurations:Dist"
        defines "TR_DIST"
        runtime "Release"
        optimize "Speed"