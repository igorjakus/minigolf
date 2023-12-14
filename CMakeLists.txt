cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

project(mini_golf)

include(cmake/PreventInSourceBuild.cmake)

set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ProjectOptions.cmake)
include(ProjectOptions.cmake)
project_options_setup()
project_local_options()

target_compile_features(project_options INTERFACE cxx_std_${CMAKE_CXX_STANDARD})

include_directories(src)

add_library(project::project_options ALIAS project_options)
add_library(project::project_warnings ALIAS project_warnings)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${PROJECT_NAME}")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(__DEBUG__)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
	add_compile_definitions(__DIST__)
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
	add_compile_definitions(__RELEASE__)
endif()

if(CMAKE_CXX_COMPILER STREQUAL "cl")
	add_compile_definitions(__COMPILER_CL__)
elseif(CMAKE_CXX_COMPILER STREQUAL "clang-cl")
	add_compile_definitions(__COMPILER__CLANG_CL__)
elseif(CMAKE_CXX_COMPILER STREQUAL "g++")
	add_compile_definitions(__COMPILER__GCC__)
elseif(CMAKE_CXX_COMPILER STREQUAL "clang++")
	add_compile_definitions(__COMPILER__CLANG__)
endif()

add_compile_definitions(GLM_FORCE_CXX11)

add_subdirectory(src)
