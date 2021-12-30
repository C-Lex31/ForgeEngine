workspace "IrisEngine"

   architecture "x64"
   configurations
   {
		  "Debug",
		  "Release",
		  "Dist"
   }

outputdir ="%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir ={}
IncludeDir["GLFW"] = "dependencies/Libraries/GLFW/include"
IncludeDir["GLAD"] = "dependencies/Libraries/GLAD/include"

IncludeDir["UI"]  =  "vendor/UI/central"

include "dependencies/Libraries/GLFW"
include "dependencies/Libraries/GLAD"
include "vendor/UI/central"


project "engine"
      
        location "engine"
		kind "StaticLib"
		language "C++"
		cppdialect "C++17"
		staticruntime "on"

		targetdir("binaries/" .. outputdir .. "/%{prj.name}")
		objdir("obj/" .. outputdir .. "/%{prj.name}")

		pchheader "irpch.h"
		pchsource "engine/source/irpch.cpp"

		 files
         {
          "%{prj.name}/source/**.h",
          "%{prj.name}/source/**.cpp"
         }

		 defines{
			  "_CRT_SECURE_NO_WARNINGS"
		 }

		 includedirs
		 {
			   "%{prj.name}/source",
			  "vendor/thirdparty/LOG/include",
			  "dependencies/Libraries/GLM",
			  "%{IncludeDir.GLFW}",
			   "%{IncludeDir.GLAD}",
			   "%{IncludeDir.UI}"
			  
		 }

		 links
		 {
		      "GLFW",
			  "GLAD",
			  "ImGui",
			  "opengl32.lib"
		 }


		 filter "system:windows"
			
			staticruntime "on"
			systemversion "latest"

			defines
			{
			   "IR_PLATFORM_WINDOWS",
			   "IR_BUILD_DLL",
			   "GLFW_INCLUDE_NONE"
			}

			filter "configurations:Debug"
					 defines "IR_DEBUG"
					 buildoptions "/MDd"
					 symbols "on"

			filter "configurations:Release"
					defines "IR_RELEASE"
					buildoptions "/MD"
					optimize "on"

			filter "configurations:Dist"
					defines "IR_DIST"
					buildoptions "/MD"
					optimize "on"

			

 project "IrisApplication"

		 location "runtime"
		 kind "ConsoleApp"
		 language "C++"
		 cppdialect "C++17"
		 staticruntime "on"

		 targetdir ("binaries/" .. outputdir .. "/%{prj.name}")
		 objdir ("obj/" .. outputdir .. "/%{prj.name}")       

		  files
         {
          "%{prj.name}/source/**.h",
          "%{prj.name}/source/**.cpp"
         }

		 includedirs
		 {
		      "vendor/thirdparty/LOG/include",
			   "dependencies/Libraries/GLM/glm",
			  "vendor/UI/central",
			  "engine/source",
			  "%{IncludeDir.GLFW}",
			  "%{IncludeDir.GLAD}"
			 
		 }

		 links
		 {
			 "engine",
			 "GLFW",
			  "GLAD"
			
		 }

		 filter "system:windows"
			
			staticruntime "on"
			systemversion "latest"

			defines
			{
			   "IR_PLATFORM_WINDOWS"
			}

			 filter "configurations:Debug"
					 defines "IR_DEBUG"
			         buildoptions "/MDd"
					 symbols "on"

			filter "configurations:Release"
					defines "IR_RELEASE"
					
					optimize "on"

			filter "configurations:Dist"
					defines "IR_DIST"
			
					optimize "on"

			
