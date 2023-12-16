cmake_minimum_required(VERSION 3.1...3.27 FATAL_ERROR)
project(imgui)

set(IM_GUI_SOURCES
imconfig.h
imgui.cpp
imgui.h
imgui_demo.cpp
imgui_draw.cpp
imgui_internal.h
imgui_tables.cpp
imgui_widgets.cpp
imstb_rectpack.h
imstb_textedit.h
imstb_truetype.h
imgui_impl_opengl3.cpp
imgui_impl_opengl3.h
imgui_impl_glfw.cpp
imgui_impl_glfw.h
imgui_impl_opengl3_loader.h
)

add_library(imgui ${IM_GUI_SOURCES})

target_include_directories(imgui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(imgui PRIVATE glfw)

