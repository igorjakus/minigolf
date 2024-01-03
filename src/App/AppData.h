// AppData.h 
//
// A simple utility class meant to group major App systems
// Note: scene-dependent systems should be owned by individual scenes

#pragma once

#include "SceneManager.h"
#include "Shader.h"
#include "Window.h"
#include "Sus/Sus.h"

namespace golf {


class AppData {

public:

	static void init(uint width, uint height, const std::string& title);
	static void terminate();

	static SceneManager& getSceneManager();
	static agl::Window& getWindow();
	static agl::Shader& getGlobalShader();
	static Sus& getSus();

private:
	AppData() = default;

	static AppData& getInstance();
	
	std::unique_ptr<agl::Window> s_window;
	std::unique_ptr<agl::Shader> s_globalShader;
	std::unique_ptr<SceneManager> s_sceneManager;
	std::unique_ptr<Sus> s_us;
	//std::unique_ptr<System> s_someOtherSystem;
};


}
