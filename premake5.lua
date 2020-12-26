project "enTT"
	kind "StaticLib"
	language "C++"


	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
        "single_include/**.hpp",
		"src/**.cpp",
        "src/**.hpp",
        "src/**.h"
	}

	includedirs
	{
        "src",
        "single_include"
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime "on"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"