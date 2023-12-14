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
	add_compile_definitions(__RELEASE__)
else()
	add_compile_definitions(__DIST__)
endif()

add_subdirectory(src)
