project "Glad"
	kind "StaticLib"
	language "C"
	staticruntime "off"
	warnings "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/glad/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c"
	}

	includedirs
	{
		"include"
	}

    filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		buildoptions "/MDd"
		symbols "On"

	filter { "system:windows", "configurations:Debug-AS" }	
		runtime "Debug"
		buildoptions "/MDd"
		symbols "On"
		sanitize { "Address" }
		flags { "NoRuntimeChecks", "NoIncrementalLink" }

	filter "configurations:Release"
		runtime "Release"
		buildoptions "/MD"
		optimize "Speed"

    filter "configurations:Dist"
		runtime "Release"
		buildoptions "/MD"
		optimize "Speed"
        symbols "Off"