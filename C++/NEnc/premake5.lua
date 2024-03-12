project (path.getbasename(path.getabsolute('.')))
    kind "ConsoleApp"
    language "C++"
    targetdir "%{cfg.platform}/%{cfg.buildcfg}"
    objdir "%{cfg.platform}/%{cfg.buildcfg}/Intermediate"
    cppdialect 'C++latest'

    files {
        'src/**.cpp',
        'include/**.hpp',
        'premake5.lua',
    }
    
    includedirs { 'include' }

    vpaths {
        ["Headers/*"] = "include/**.hpp",
        ["Sources"] = "src/**.cpp",
        ["*"] = "premake5.lua"
    }