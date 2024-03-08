workspace "NEnc"
    configurations { 'Debug', 'Release' }
    platforms { 'x86', 'x64' }

    includedirs { 'include' }

    characterset 'MBCS'
    pic 'On'
    symbols 'On'
    flags 'MultiProcessorCompile'

    filter 'configurations:Debug'
        defines { '_DEBUG' }
        targetsuffix '_d'
        runtime 'Debug'

    filter 'configurations:Release'
        optimize 'Full'
        runtime 'Release'

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
    
    filter "system:windows"
        defines { "_WIN32" }
        preferredtoolarchitecture 'x86_64'
        staticruntime 'On'
        buildoptions { '/Zc:__cplusplus' }

    project "NEnc"
        kind "ConsoleApp"
        language "C++"
        targetdir "bin/%{cfg.buildcfg}"
        cppdialect 'C++latest'

        files {
            'src/**.cpp',
            'include/**.hpp',
            'premake5.lua',
        }

        vpaths {
            ["Headers/*"] = "include/**.hpp",
            ["Sources"] = "src/**.cpp",
            ["*"] = "premake5.lua"
        }