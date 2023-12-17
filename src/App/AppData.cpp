#include "AppData.h"

namespace golf {


void AppData::init(uint width, uint height, std::string title) {
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
	SceneManager();
}

SceneManager& AppData::SceneManager() {
	return SceneManager::getInstance();
}

agl::Window& AppData::Window() {
	return *s_window;
}


}
