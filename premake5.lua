include "./Vendor/premake/premake_customization/solution_items.lua"

workspace "Evil"
	architecture "x86_64"
	startproject "EvilEditor"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	-- Include directories relative to root folder (solution directory)
	IncludeDir = {}
	IncludeDir["GLFW"] = "%{wks.location}/Evil/Vendor/GLFW/include"
	IncludeDir["Glad"] = "%{wks.location}/Evil/Vendor/Glad/include"
	IncludeDir["ImGui"] = "%{wks.location}/Evil/Vendor/imgui"
	IncludeDir["glm"] = "%{wks.location}/Evil/Vendor/glm"
	IncludeDir["stb_image"] = "%{wks.location}/Evil/Vendor/stb_image"
	IncludeDir["entt"] = "%{wks.location}/Evil/Vendor/entt/include"

	group "Dependencies"
	include "Vendor/premake"
	include "Evil/Vendor/GLFW"
	include "Evil/Vendor/Glad"
	include "Evil/Vendor/imgui"
	group ""

	include "Evil"
	include "Sandbox"
	include "EvilEditor"