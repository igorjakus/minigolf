function(setup_dependencies)
	add_subdirectory(src/AGL-Deps/GLAD)	
	add_subdirectory(src/AGL-Deps/GLFW)	
	add_subdirectory(src/AGL-Deps/glm)	
	add_subdirectory(src/AGL-Deps/stb)	

	include_directories(src/AGL-Deps/GLFW/include)
	include_directories(src/AGL-Deps/GLAD/include)
endfunction()

setup_dependencies()
