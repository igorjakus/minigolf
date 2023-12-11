set(DTL_SOURCES

	dtl.cpp
	dtl.h

)

add_library(lib_dtl ${DTL_SOURCES})

target_link_libraries(lib_dtl PRIVATE project_options project_warnings)

target_include_directories(lib_dtl PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_compile_features(lib_dtl PUBLIC cxx_std_20)

target_compile_definitions(lib_dtl PUBLIC SAMPLE_LIBRARY_STATIC_DEFINE)
