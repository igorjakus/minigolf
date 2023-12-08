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
	option(project_WARNINGS_AS_ERRORS "Treat Warnings As Errors" ON)
	option(project_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
	option(project_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" ${SUPPORTS_ASAN})
	option(project_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
	option(project_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" ${SUPPORTS_UBSAN})
	option(project_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
	option(project_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
	option(project_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
	option(project_ENABLE_CLANG_TIDY "Enable clang-tidy" ON)
	option(project_ENABLE_PCH "Enable precompiled headers" OFF)
	option(project_ENABLE_CACHE "Enable ccache" ON)
endmacro()

macro(project_local_options)
	# standard project settings here

	add_library(project_warnings INTERFACE)
	add_library(project_options INTERFACE)

	include(cmake/CompilerWarnings.cmake)
	set_project_warnings(
		project_warnings
		${project_WARNINGS_AS_ERRORS}
		""
		""
		""
		""
	)

	# user-selected linker

	# satanizers

	# set_properties()

	# i tak dalej wszystko po kolei

endmacro()
