set(SOURCES 

	App.cpp

)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE project::project_options
		  project::project_warnings)
