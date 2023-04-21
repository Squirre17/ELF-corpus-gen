add_rules("mode.debug", "mode.release")

target("ELF-corpus-gen")
    set_kind("binary")
    
    add_cxxflags("-std=c++17")
    add_cxxflags("-no-pie")
    add_cxxflags("-fsanitize=address")
    add_ldflags("-fsanitize=address")

    add_includedirs("inc/common")
    add_includedirs("inc")
    add_files("src/*.cpp")

