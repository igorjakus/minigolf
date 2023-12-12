cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

project(mini_golf)

include(cmake/PreventInSourceBuild.cmake)

include(ProjectOptions.cmake)
project_options_setup()
project_local_options()

target_compile_features(project_options INTERFACE cxx_std_${CMAKE_CXX_STANDARD})

# include(ProjectDependencies.cmake)

include_directories(src)

add_library(project::project_options ALIAS project_options)
add_library(project::project_warnings ALIAS project_warnings)

add_subdirectory(src)
