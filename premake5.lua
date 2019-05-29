workspace "Graphics"
    architecture "x64"
    startproject "Graphics"

    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "vendor/GLFW/include"
IncludeDir["Glad"] = "vendor/Glad/include"
IncludeDir["ImGui"] = "vendor/imgui"
IncludeDir["glm"] = "vendor/glm"
IncludeDir["spdlog"] = "vendor/spdlog/include"

include "vendor/GLFW"
include "vendor/Glad"
include "vendor/imgui"

project "Graphics"
    location "graphics"
    kind "ConsoleApp"
    language "C++"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "pch.h"
    pchsource "Graphics/src/pch.cpp"

    files
    {
        "%{prj.name}/src/**",
        "%{prj.name}/res/**",
        "%{prj.name}/imgui.ini",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl",
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
    }

    links 
    { 
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "APP_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "APP_RELEASE"
        runtime "Release"
        optimize "On"

project "Graphics.UnitTests"
    location "graphics.unittests"
    kind "ConsoleApp"
    language "C++"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "pch.h"
    pchsource "Graphics.UnitTests/src/pch.cpp"

    files
    {
        "%{prj.name}/src/**",
    }

    links 
    { 
        "Graphics"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

    filter "configurations:Debug"
        defines "APP_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "APP_RELEASE"
        runtime "Release"
        optimize "On"
