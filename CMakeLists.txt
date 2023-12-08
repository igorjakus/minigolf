cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

project(mini_golf)

include(cmake/PreventInSourceBuild.cmake)

set(SOURCES 

	AGL/main.cpp
	AGL/Core.cpp
	AGL/Core.h
	AGL/Shader.cpp
	AGL/Shader.h
	AGL/Window.cpp
	AGL/Window.h
)

add_executable(${PROJECT_NAME} ${SOURCES})
