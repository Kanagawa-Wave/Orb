-- premake5.lua
workspace "Orb"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "OrbEditor"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

outputdir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "Core"
	include "OrbCore/Build-Core.lua"
   include "OrbCore/External/glfw"
group ""

include "OrbEditor/Build-Editor.lua"