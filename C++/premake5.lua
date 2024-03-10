workspace "C++ Portfolio"
    configurations { 'Debug', 'Release' }
    platforms { 'x86', 'x64' }

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
    
    
    include 'Calculator'
    include 'NEnc'