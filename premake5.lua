workspace "Iris"

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

IncludeDir["UI"]  =  "vendor/UI/main"

include "dependencies/Libraries/GLFW"
include "dependencies/Libraries/GLAD"
include "vendor/UI/main"


project "IrisEngine"
      
        location "IrisEngine"
		kind "StaticLib"
		language "C++"
		staticruntime "On"

		targetdir("bin/" .. outputdir .. "/%{prj.name}")
		objdir("obj/" .. outputdir .. "/%{prj.name}")

		pchheader "irpch.h"
		pchsource "IrisEngine/src/irpch.cpp"

		 files
         {
          "%{prj.name}/src/**.h",
          "%{prj.name}/src/**.cpp"
         }

		 defines{
			  "_CRT_SECURE_NO_WARNINGS"
		 }

		 includedirs
		 {
			   "%{prj.name}/src",
			  "vendor/thirdparty/LOG/include",
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

		 postbuildcommands
		 {
				   ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")

		 }

		 filter "system:windows"
			cppdialect "C++17"
			staticruntime "On"
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
					 symbols "On"

			filter "configurations:Release"
					defines "IR_RELEASE"
					buildoptions "/MD"
					optimize "On"

			filter "configurations:Dist"
					defines "IR_DIST"
					buildoptions "/MD"
					optimize "On"

			

 project "Sandbox"

		 location "Sandbox"
		 kind "ConsoleApp"
		 language "C++"
		 staticruntime "On"

		 targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		 objdir ("obj/" .. outputdir .. "/%{prj.name}")       

		  files
         {
          "%{prj.name}/src/**.h",
          "%{prj.name}/src/**.cpp"
         }

		 includedirs
		 {
		      "vendor/thirdparty/LOG/include",
			  "vendor/UI/main",
			  "IrisEngine/src",
			  "%{IncludeDir.GLFW}",
			  "%{IncludeDir.GLAD}"
			 
		 }

		 links
		 {
			 "IrisEngine",
			 "GLFW",
			  "GLAD"
			
		 }

		 filter "system:windows"
			cppdialect "C++17"
			staticruntime "On"
			systemversion "latest"

			defines
			{
			   "IR_PLATFORM_WINDOWS"
			  
			}

			 filter "configurations:Debug"
					 defines "IR_DEBUG"
			         buildoptions "/MDd"
					 symbols "On"

			filter "configurations:Release"
					defines "IR_RELEASE"
					
					optimize "On"

			filter "configurations:Dist"
					defines "IR_DIST"
			
					optimize "On"

			
