workspace "Velocity"
	architecture "x64"
	configurations {"Debug", "Release", "Dist"}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Velocity"
	location "Velocity"
	kind "SharedLib"
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
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"VL_PLATFORM_WINDOWS",
			"VL_BUILD_DLL"			
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
		
	filter "configurations:Debug"
		defines "VL_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "VL_RELEASE"
		optimize"On"
		
	filter "configurations:Dist"
		defines "VL_DIST"
		optimize"On"
		
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	
	targetdir  ("bin/" .. outputdir .. "/%{prj.name}")
	objdir  ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs 
	{
		"Velocity/vendor/spdlog/include",
		"Velocity/src"
	}
	
	links{ "Velocity" }
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"VL_PLATFORM_WINDOWS",		
		}
		
	filter "configurations:Debug"
		defines "VL_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "VL_RELEASE"
		optimize"On"
		
	filter "configurations:Dist"
		defines "VL_DIST"
		optimize"On"