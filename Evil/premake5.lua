project "Evil"
		kind "StaticLib"
		language "C++"
		cppdialect "C++17"
		staticruntime "on"

		targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
		objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

		pchheader "evilpch.h"
		pchsource "src/evilpch.cpp"

		files
		{
			"src/**.h",
			"src/**.cpp",
			"Vendor/stb_image/**.h",
			"Vendor/stb_image/**.cpp",
			"Vendor/glm/glm/**.hpp",
			"Vendor/glm/glm/**.inl",
		}

		defines
		{
			"_CRT_SECURE_NO_WARNINGS",
			"GLFW_INCLUDE_NONE"
		}

		includedirs
		{
			"src",
			"Vendor/spdlog/include",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.Glad}",
			"%{IncludeDir.ImGui}",
			"%{IncludeDir.glm}",
			"%{IncludeDir.stb_image}",
			"%{IncludeDir.entt}"
		}

		links
		{
			"GLFW",
			"Glad",
			"ImGui",
			"opengl32.lib"
		}

		filter "system:windows"
			systemversion "latest"

			defines
			{

			}

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