set(AGL_SOURCES

	Core.cpp
	Core.h
	Shader.cpp
	Shader.h
	Window.cpp
	Window.h

)

add_library(lib_agl ${AGL_SOURCES})

target_link_libraries(lib_agl PRIVATE project_options project_warnings)

target_include_directories(lib_agl PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_compile_features(lib_agl PUBLIC cxx_std_20)

target_compile_definitions(lib_agl PUBLIC SAMPLE_LIBRARY_STATIC_DEFINE)

target_link_libraries(lib_agl PRIVATE lib_dtl)
