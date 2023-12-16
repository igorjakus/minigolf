# Main source control file 
#
# Source:
# 
# https://github.com/cpp-best-practices/cmake_template/blob/main/ProjectOptions.cmake

include(CMakeDependentOption)
include(CheckCXXCompilerFlag)

macro(project_sanitizers_support)
	if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND NOT WIN32)
		set(SUPPORTS_UBSAN ON)
	else()
		set(SUPPORTS_UBSAN OFF)
	endif()

	if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND WIN32)
		set(SUPPORTS_ASAN OFF)
	else()
		set(SUPPORTS_ASAN ON)
	endif()
endmacro()

macro(project_options_setup)
	option(project_ENABLE_IPO "Enable IPO/LTO" ON)
	option(project_WARNINGS_AS_ERRORS "Treat Warnings As Errors" OFF)
	option(project_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
	option(project_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" ${SUPPORTS_ASAN})
	option(project_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
	option(project_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" ${SUPPORTS_UBSAN})
	option(project_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
	option(project_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
	option(project_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
	option(project_ENABLE_CLANG_TIDY "Enable clang-tidy" ON)
	option(project_ENABLE_CACHE "Enable ccache" ON)
endmacro()

macro(project_local_options)
	# standard project settings here

	set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

	add_library(project_warnings INTERFACE)
	add_library(project_options INTERFACE)

	if(NOT ${project_WARNINGS_AS_ERRORS})
		message("######################################################")
		message("Warning: compiler warnings not treated as errors")
		message("It is recommended to se the WARNINGS_AS_ERRORS option to ON")
		message("######################################################")
	endif()

	include(cmake/CompilerWarnings.cmake)
	set_project_warnings(
		project_warnings
		${project_WARNINGS_AS_ERRORS}
		""
		""
		""
		""
	)

	include(cmake/ClangTidy.cmake)
	if(project_ENABLE_CLANG_TIDY)
		project_enable_clang_tidy(project_options ${project_WARNINGS_AS_ERRORS})
	endif()

	# user-selected linker

	# satanizers

	# set_properties()

	# i tak dalej wszystko po kolei

endmacro()
