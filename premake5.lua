function DeclareCommon()
    staticruntime "Off"
    floatingpoint "Fast"
    -- vectorextensions "AVX2"

    -- versions
    systemversion "10.0"
    toolset "v143"
    cppdialect "C++20"

    -- build output options
    outputdir = "%{cfg.buildcfg}" -- "Release/x32" / "Release/x64" / "Debug/x32" / "Debug/x64"
    targetdir   ("bin/" .. outputdir)
    objdir      ("bin/int/" .. outputdir .. "/%{prj.name}")
    libdirs     ("bin/" .. outputdir .. "/%{prj.name}")

    --
    defines {
        "_CRT_SECURE_NO_WARNINGS", -- removes pesky warnings to use Microsoft "safer" variants of certain std:: functions
        "NOMINMAX", -- excludes certain MINMAX macros
        "WIN32_LEAN_AND_MEAN", -- excludes certain includes that we do not require from Windows.h
		"CHANGE_G3LOG_DEBUG_TO_DBUG",
    }

	flags {
		"LinkTimeOptimization",
		"Maps",
		"NoImportLib",
		"MultiProcessorCompile"
	}
end

function DeclareDebug()
	filter "configurations:Debug"
		flags {  }
		symbols "On"
		editandcontinue "Off"
		defines { "DEBUG" }

	filter "configurations:Release"
		flags { "NoManifest" }
		defines { "RELEASE", "NDEBUG" }
		optimize "speed"

	filter "configurations:Dist"
		flags { "FatalWarnings", "NoManifest" }
		defines { "DIST", "NDEBUG" }
		optimize "speed"
end

function does_file_exist(file)
    local f = io.open(file,"r")
    if f ~= nil then
        io.close(f)

        return true
    end

    return false
end

workspace "BaseDX11App"
    startproject "BaseDX11App"

    configurations { "Debug", "Release" }
    platforms { "x64", "x32" }

    project "BaseDX11App"
        location "src/"
		kind "ConsoleApp"
        language "C++"

        includedirs {
			"vendor/g3log/src",
			"vendor/imgui",
            "src/"
        }

        files {
            "src/**.hpp",
            "src/**.cpp",
            "src/**.asm"
        }

        libdirs {
            "bin/lib"
        }

        links {
			"d3d11",
			"g3log",
            "imgui"
        }

        pchheader "common.hpp"
        pchsource "src/common.cpp"

        DeclareCommon()
		DeclareDebug()

    project "g3log"
        location "vendor/%{prj.name}"
        kind "StaticLib"
        language "C++"

        includedirs {
            "vendor/%{prj.name}/src"
        }

        if not does_file_exist("vendor\\g3log\\src\\g3log\\generated_definitions.hpp") then
            file = io.open("vendor\\g3log\\src\\g3log\\generated_definitions.hpp", "w")

            if file == nil then
                premake.error("Failed to location g3log vendor directory, did you pull with --recurse?")
            end

            file:write("#pragma once")
        end

        files {
            "vendor/%{prj.name}/src/**.hpp",
            "vendor/%{prj.name}/src/**.cpp"
        }

        removefiles {
			"vendor/%{prj.name}/src/crashhandler_unix.cpp"
        }

        DeclareCommon()
		DeclareDebug()

    project "imgui"
        location "vendor/%{prj.name}"
        kind "StaticLib"
        language "C++"

        files {
            "vendor/%{prj.name}/imgui.cpp",
            "vendor/%{prj.name}/imgui_draw.cpp",
            "vendor/%{prj.name}/imgui_tables.cpp",
            "vendor/%{prj.name}/imgui_widgets.cpp",
            "vendor/%{prj.name}/backends/imgui_impl_dx11.cpp",
            "vendor/%{prj.name}/backends/imgui_impl_win32.cpp"
        }

        includedirs {
            "vendor/%{prj.name}"
        }
		
		defines {
			"IMGUI_DISABLE_DEMO_WINDOWS",
			"IMGUI_DISABLE_METRICS_WINDOW",
			"IM_ASSERT(_EXPR) ((void)(_EXPR))"
		}

        DeclareCommon()
		DeclareDebug()