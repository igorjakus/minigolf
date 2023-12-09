cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

project(mini_golf)

include(cmake/PreventInSourceBuild.cmake)

set(SOURCES 

	App/App.cpp
	AGL/Core.cpp
	AGL/Core.h
	AGL/Shader.cpp
	AGL/Shader.h
	AGL/Window.cpp
	AGL/Window.h
	DTL/dtl.cpp
	DTL/dtl.h
)

add_subdirectory(AGL-Deps/GLAD)	
add_subdirectory(AGL-Deps/GLFW)	
add_subdirectory(AGL-Deps/glm)	
add_subdirectory(AGL-Deps/stb)	

include_directories(AGL-Deps/glfw/include)
include_directories(pch)
include_directories(DTL)
include_directories(AGL)

add_executable(${PROJECT_NAME} ${SOURCES})

target_precompile_headers(${PROJECT_NAME} PUBLIC pch/pch.h)

target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE glm glfw 
	glad stb)