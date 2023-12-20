// AppData.h 
//
// A simple utility class meant to group major App systems
// Note: scene-dependent systems should be owned by individual scenes

#pragma once

#include "SceneManager.h"
#include "Window.h"

namespace golf {


class AppData {

public:
	AppData() = delete;

	static void init(uint width, uint height, const std::string& title);

	static SceneManager& getSceneManager();
	static agl::Window& getWindow();

private:

	static std::unique_ptr<agl::Window> s_window; //NOLINT
	
};


}
