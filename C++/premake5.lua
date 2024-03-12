if os.host() == 'windows' then
    os.execute('dir /B > files.txt')
else
    os.execute('ls -1 > files.txt')
end

local rawFiles = io.readfile('files.txt')
os.remove('files.txt')

local files = string.explode(rawFiles,'\r\n')
for k,v in pairs(files) do
    if not v or v == '' or v == ' ' then files[k] = nil end
end

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
    
    for k,v in ipairs(files) do
        if os.isdir(v) then
            if not string.startswith('.') then
                include (v)
            end
        end
    end