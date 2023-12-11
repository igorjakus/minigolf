include_directories(AGL-Deps)

include_directories(pch)

add_subdirectory(AGL)
add_subdirectory(DTL)

add_subdirectory(App)

target_precompile_headers(${PROJECT_NAME} PUBLIC pch/pch.h)

target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE glm glfw glad stb lib_agl lib_dtl)
