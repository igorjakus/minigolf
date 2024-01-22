// AppData.h 
//
// A simple utility class meant to group major App systems
// Note: scene-dependent systems should be owned by individual scenes

#pragma once

#include "Sus/Sus.h"
#include "SceneManager/SceneManager.h"
#include "Input/UserInput.h"

#include "Window.h"

namespace golf {


class AppData {

public:

	static void init(uint width, uint height, const std::string& title);
	static void terminate();

	static agl::Window& getWindow();
	static Sus& getSus();
	static SceneManager& getSceneManager();
	static Input& getInput();

private:
	AppData() = default;

	static AppData& getInstance();

	std::unique_ptr<agl::Window> m_window;
	std::unique_ptr<Sus> m_sus;
	std::unique_ptr<SceneManager> m_sceneManager;
	std::unique_ptr<Input> m_input;

	//std::unique_ptr<System> s_someOtherSystem;
};


}
