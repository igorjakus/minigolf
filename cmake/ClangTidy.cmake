# Source: 
#
# https://github.com/cpp-best-practices/cmake_template/blob/main/cmake/StaticAnalyzers.cmake

macro(project_enable_clang_tidy target WARNINGS_AS_ERRORS)

	find_program(CLANGTIDY clang-tidy)
	if(CLANGTIDY AND CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
		# construct the clang-tidy command line
		set(CLANG_TIDY_OPTIONS
		${CLANGTIDY}
		-extra-arg=-Wno-unknown-warning-option
		-extra-arg=-Wno-ignored-optimization-argument
		-extra-arg=-Wno-unused-command-line-argument
		-p)
		# set standard
		if(NOT
	   "${CMAKE_CXX_STANDARD}"
	   STREQUAL
	   "")
			if("${CLANG_TIDY_OPTIONS_DRIVER_MODE}" STREQUAL "cl")
				set(CLANG_TIDY_OPTIONS ${CLANG_TIDY_OPTIONS} -extra-arg=/std:c++${CMAKE_CXX_STANDARD})
			else()
				set(CLANG_TIDY_OPTIONS ${CLANG_TIDY_OPTIONS} -extra-arg=-std=c++${CMAKE_CXX_STANDARD})
			endif()
		endif()

		# set warnings as errors
		if(${WARNINGS_AS_ERRORS})
			list(APPEND CLANG_TIDY_OPTIONS -warnings-as-errors=*)
		endif()

		message("clang-tidy set globally")
		set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_OPTIONS})
	elseif(NOT CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
		message(${WARNING_MESSAGE} "Not using clang-tidy since clang is not used")
	else()
		message(${WARNING_MESSAGE} "clang-tidy requested but executable not found")
	endif()
endmacro()
