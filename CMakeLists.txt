cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

project(mini_golf)

include(cmake/PreventInSourceBuild.cmake)

include(ProjectOptions.cmake)
project_options_setup()
project_local_options()

set(SOURCES 
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
