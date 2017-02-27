includeexternal ("premake-vs-include.lua")

workspace "basic-test"
    language "C++"
    location "build/%{_ACTION}/%{wks.name}"    
    if _ACTION == "vs2015" then
        toolset "v140_xp"
    end

    group "memory-zip"    
        project "ZipDLL"            
            kind "SharedLib"                         
            files
            {
                "ZipDLL/*.def",   
                "ZipDLL/**.h",
                "ZipDLL/**.cpp", 
                "ZipDLL/**.c"
                
            }   
        
        create_console_project("ZipTest", ".")
            links
            {
                "ZipDLL"
            }