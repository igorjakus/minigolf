set(AGL_SOURCES

	Agl.cpp
	Agl.h
	Shader.cpp
	Shader.h
	Window.cpp
	Window.h

)

add_library(lib_agl ${AGL_SOURCES})

# Apply project options to this library
target_link_libraries(lib_agl PRIVATE project::project_options project::project_warnings)

# Library build
target_include_directories(lib_agl PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_compile_features(lib_agl PUBLIC cxx_std_20)
target_compile_definitions(lib_agl PUBLIC SAMPLE_LIBRARY_STATIC_DEFINE)

# link dependencies
target_link_libraries(lib_agl PRIVATE glm glfw glad stb lib_dtl)
if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
target_link_libraries(lib_agl PRIVATE imgui)
endif()