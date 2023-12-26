#include "AppData.h"

namespace golf {


std::unique_ptr<agl::Window> AppData::s_window = nullptr; //NOLINT
std::unique_ptr<agl::Shader> AppData::s_globalShader; //NOLINT

void AppData::init(uint width, uint height, const std::string& title) {

	// Window creation
	s_window = std::make_unique<agl::Window>(width, height, title);

	s_window->create();

	glm::uvec2 screenRes = s_window->getScreenResolution(); 
	const uint windowPosX = screenRes.x / 2 - width / 2;
	const uint windowPosY = screenRes.y / 2 - height / 2;
	s_window->setWindowPos(windowPosX, windowPosY);

	s_window->setIcon("assets/icon/icon.png", "assets/icon/icon.png");

	// Global shader creation
	s_globalShader = std::make_unique<agl::Shader>("assets/shaders/DefaultShader.glsl");

	// Scene manager initialization
	getSceneManager();
}

SceneManager& AppData::getSceneManager() {
	return SceneManager::getInstance();
}

agl::Window& AppData::getWindow() {
	#ifdef __DEBUG__
	if(!s_window) {
		DTL_ERR("Attempt to access window before it is inicialized!");
	}
	#endif
	return *s_window;
}

agl::Shader& AppData::getGlobalShader() {
	return *s_globalShader;
}


}
