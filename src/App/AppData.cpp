#include "AppData.h"

namespace golf {


std::unique_ptr<agl::Window> AppData::s_window;

void AppData::init(uint width, uint height, const std::string& title) {
	// Window creation
	s_window = std::make_unique<agl::Window>(width, height, title);

	s_window->create();

	uint screenX = 0;
	uint screenY = 0;
	s_window->getScreenResolution(screenX, screenY); 
	const uint windowPosX = screenX / 2 - width / 2;
	const uint windowPosY = screenY / 2 - height / 2;
	s_window->setWindowPos(windowPosX, windowPosY);

	s_window->setIcon("assets/icon/icon.png", "assets/icon/icon.png");

	// Other systems initialization
	getSceneManager();
}

SceneManager& AppData::getSceneManager() {
	return SceneManager::getInstance();
}

agl::Window& AppData::getWindow() {
	return *s_window;
}

Input& AppData::getInput() {
	return Input::getInstance();
}


}
