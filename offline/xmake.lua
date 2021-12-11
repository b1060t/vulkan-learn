add_requires("glfw", "glm", "glew", "opengl")

package("mango")

target("offline-renderer")
	set_kind("binary")
	add_includedirs("src")
	add_includedirs("src/ogl")
	add_files("./main.cpp")
	add_packages("glfw", "glm", "glew", "opengl")