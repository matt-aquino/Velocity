workspace "Velocity"
	architecture "x64"
	configurations {"Debug", "Release", "Dist"}
	startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Velocity/vendor/GLFW/include"
IncludeDir["GLAD"] = "Velocity/vendor/glad/include"
IncludeDir["ImGui"] = "Velocity/vendor/ImGui"
IncludeDir["glm"] = "Velocity/vendor/glm"
include "Velocity/vendor/GLFW"
include "Velocity/vendor/GLAD"
include "Velocity/vendor/ImGui"


project "Velocity"
	location "Velocity"
	kind "SharedLib"
	language "C++"
	staticruntime "off"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "vlpch.h"
	pchsource "Velocity/src/vlpch.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}
	
	includedirs 
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}
	
	links
	{
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		
		defines
		{
			"VL_PLATFORM_WINDOWS",
			"VL_BUILD_DLL",
			"GLFW_INCLUDE_NONE"			
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
		
	filter "configurations:Debug"
		defines "VL_DEBUG"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "VL_RELEASE"
		runtime "Release"
		optimize"On"
		
	filter "configurations:Dist"
		defines "VL_DIST"
		runtime "Release"
		optimize"On"
		
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"
	
	targetdir  ("bin/" .. outputdir .. "/%{prj.name}")
	objdir  ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",

	}
	
	includedirs 
	{
		"Velocity/vendor/spdlog/include",
		"Velocity/src",
		"%{IncludeDir.glm}"
	}
	
	links{ "Velocity" }
	
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		
		defines
		{
			"VL_PLATFORM_WINDOWS",		
		}
		
	filter "configurations:Debug"
		defines "VL_DEBUG"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "VL_RELEASE"
		runtime "Release"
		optimize"On"
		
	filter "configurations:Dist"
		defines "VL_DIST"
		runtime "Release"
		optimize"On"