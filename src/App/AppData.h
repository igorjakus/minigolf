// AppData.h 
//
// A simple utility class meant to group major App systems
// Note: scene-dependent systems should be owned by individual scenes

#pragma once

#include "SceneManager.h"
#include "UserInput.h"
#include "Shader.h"
#include "Window.h"

namespace golf {


class AppData {

public:

	static void init(uint width, uint height, const std::string& title);
	static void terminate();

	static agl::Window& getWindow();
	static agl::Shader& getGlobalShader();
	static SceneManager& getSceneManager();
	static Input& getInput();

private:
	AppData() = default;

	static AppData& getInstance();
	
	std::unique_ptr<agl::Window> s_window;
	std::unique_ptr<agl::Shader> s_globalShader;
	std::unique_ptr<SceneManager> s_sceneManager;
	//std::unique_ptr<System> s_someOtherSystem;
};


}
