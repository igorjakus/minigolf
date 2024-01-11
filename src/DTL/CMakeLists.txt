set(DTL_SOURCES

	dtl.cpp
	dtl.h

)

add_library(lib_dtl ${DTL_SOURCES})

# Apply project options to this library
if(project_LUKASZ_WARNINGS)
	target_link_libraries(lib_dtl PRIVATE project::project_options project::project_warnings)
endif()

# Library build
target_include_directories(lib_dtl PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_compile_features(lib_dtl PUBLIC cxx_std_20)
target_compile_definitions(lib_dtl PUBLIC SAMPLE_LIBRARY_STATIC_DEFINE)
