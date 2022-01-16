add_requires("vulkan-hpp", "vulkan-loader", "kompute")
add_requires("kompute")
target("kompute-sample")
	set_kind("binary")
	add_languages("cxx17")
	add_rules("utils.glsl2spv", {bin2c = true})
	add_rules("utils.bin2c", {extensions = {".spv"}})
	add_includedirs(".")
	add_files("test.cpp", "tmp.comp")
	add_packages("vulkan-hpp", "vulkan-loader", "kompute")