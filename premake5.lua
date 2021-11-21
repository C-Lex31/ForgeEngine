workspace "Iris"

   architecture "x64"
   configurations
   {
		  "Debug",
		  "Releae",
		  "Dist"
		  
   }

outputdir ="%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"




project "IrisEngine"
      
        location "engine"
		kind "SharedLib"
		language "C++"


		targetdir("bin/" .. outputdir .. "/% {prj.name}")
		objdir("bin-int/" .. outputdir .. "/% {prj.name}")

		pchheader "irpch.h"
		pchsource "IrisEngine/src/irpch.cpp"

		 files
         {
          "%{prj.name}/src/**.h",
          "%{prj.name}/src/**.cpp"
         }

		 includedirs
		 {
		     "%{prj.name}/vendor/log/include"
		 }

		 filter "system:windows"
			cppdialect "C++17"
			staticruntime "On"
			systemversion "latest"

			defines
			{
			   "IR_PLATFORM_WINDOWS",
			   "IR_BUILD_DLL"
			}

			filter "configurations:Debug"
					 defines "IR_DEBUG"
					 symbols "On"

			filter "configurations:Release"
					defines "IR_RELEASE"
					optimize "On"

			filter "configurations:Dist"
					defines "IR_DIST"
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
		     "%{prj.name}/vendor/log/include",
			 "engine/src"
		 }

		 links
		 {
			  "IrisEngine"
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
					 symbols "On"

			filter "configurations:Release"
					defines "IR_RELEASE"
					optimize "On"

			filter "configurations:Dist"
					defines "IR_DIST"
					optimize "On"

			
