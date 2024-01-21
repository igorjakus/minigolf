set(SOURCES 

	main.cpp
	App.h 
	App.cpp

	Scenes.h 
	Scenes.cpp 

	# ECS
	ECS/Entity.h
	ECS/Entity.cpp
	ECS/Component.h
	ECS/Component.cpp
	
	# Components
	Graphics.h
	Graphics.cpp
	GUI.h 
	GUI.cpp
	Slingshot.h
	Slingshot.cpp

	# Core
	Core/AppData.h
	Core/AppData.cpp 

	# SceneManager
	Core/SceneManager/SceneManager.h
	Core/SceneManager/SceneManager.cpp 
	Core/SceneManager/Scene.h
	Core/SceneManager/Scene.cpp

	# Sus
	Core/Sus/Sus.h
	Core/Sus/Sus.cpp

	# Input
	Core/Input/UserInput.h
	Core/Input/UserInput.cpp

	# Physics
	physics.cpp
	physics.h

	# CameraControls
	CameraControls.h 
	CameraControls.cpp
	
	# Scenes
	scenes/levels.cpp 
	scenes/levels.h
	scenes/misc.cpp 
	scenes/misc.h 
	scenes/transition.h 
	scenes/transition.cpp

)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE project::project_options
		  project::project_warnings)

add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
	COMMENT "Copy assets folder to executable"
)

add_dependencies(${PROJECT_NAME} copy_assets)

