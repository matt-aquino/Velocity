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
IncludeDir["entt"] = "Velocity/vendor/entt/include"
IncludeDir["stb_image"] = "Velocity/vendor/stb_image"
include "Velocity/vendor/GLFW"
include "Velocity/vendor/GLAD"
include "Velocity/vendor/ImGui"


project "Velocity"
	location "Velocity"
	kind "StaticLib"
	language "C++"
	cppdialect "C++latest"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "vlpch.h"
	pchsource "Velocity/src/vlpch.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
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
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.stb_image}",
	}
	
	links
	{
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib"
	}

	defines { "_CRT_SECURE_NO_WARNINGS" }

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"VL_PLATFORM_WINDOWS",
			"VL_BUILD_DLL",
			"GLFW_INCLUDE_NONE"			
		}
		
	filter "configurations:Debug"
		defines "VL_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "VL_RELEASE"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Dist"
		defines "VL_DIST"
		runtime "Release"
		optimize "on"
		
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++latest"
	staticruntime "on"
	
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
		"Velocity/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.stb_image}",
	}
	
	links{ "Velocity" }
	

	filter "system:windows"
		systemversion "latest"
		
		defines
		{
			"VL_PLATFORM_WINDOWS",		
		}
		
	filter "configurations:Debug"
		defines "VL_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "VL_RELEASE"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Dist"
		defines "VL_DIST"
		runtime "Release"
		optimize "on"