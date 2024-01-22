# AGL library dependencies:
add_subdirectory(AGL-Deps/GLAD)	
add_subdirectory(AGL-Deps/GLFW)	
add_subdirectory(AGL-Deps/glm)	
add_subdirectory(AGL-Deps/stb)	
if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
add_subdirectory(AGL-Deps/ImGui)	
endif()

include_directories(AGL-Deps)
include_directories(AGL-Deps/GLFW/include)
include_directories(AGL-Deps/GLAD/include)

# Precompiled headers:
include_directories(pch)

# Project libraries:
add_subdirectory(AGL)
add_subdirectory(DTL)

set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_OPTIONS})

# Utility libraries:
add_subdirectory(Util)

# Application source code:
add_subdirectory(App)

target_precompile_headers(${PROJECT_NAME} PRIVATE pch/pch.h)
target_precompile_headers(lib_agl PRIVATE pch/pch.h)
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE glm glfw glad stb lib_agl lib_dtl lib_gml)
if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE imgui)
endif()
