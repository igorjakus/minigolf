cmake_minimum_required(VERSION 3.1...3.27 FATAL_ERROR)
project(miniaudio)

add_library(miniaudio)
target_sources(miniaudio PRIVATE miniaudio.c)
target_include_directories(miniaudio PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")



