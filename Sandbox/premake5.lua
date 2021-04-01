project "Sandbox"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++17"
		staticruntime "on"

		targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
		objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

		files
		{
			"src/**.h",
			"src/**.cpp",
		}

		includedirs
		{
			"%{wks.location}/Evil/Vendor/spdlog/include",
			"%{wks.location}/Evil/src",
			"%{wks.location}/Evil/Vendor",
			"%{IncludeDir.glm}",
			"%{IncludeDir.entt}"
		}

		links
		{
			"Evil"
		}

		filter "system:windows"
			systemversion "latest"

		filter "configurations:Debug"
			defines "EVIL_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "EVIL_RELEASE"
			runtime "Release"
			optimize "on"

		filter "configurations:Dist"
			defines "EVIL_DIST"
			runtime "Release"
			optimize "on"