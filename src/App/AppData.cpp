


#include "AppData.h"


namespace golf {


AppData& AppData::getInstance() {
	static AppData instance;
	return instance;
}

void AppData::init(uint width, uint height, const std::string& title) {

	// Window creation
	getInstance().s_window = std::make_unique<agl::Window>(width, height, title);

	getInstance().s_window->create();

	glm::uvec2 screenRes = getInstance().s_window->getScreenResolution();
	const uint windowPosX = screenRes.x / 2 - width / 2;
	const uint windowPosY = screenRes.y / 2 - height / 2;
	getInstance().s_window->setWindowPos(windowPosX, windowPosY);

	getInstance().s_window->setIcon("assets/icon/icon.png", "assets/icon/icon.png");

	// Global shader creation
	getInstance().s_globalShader = std::make_unique<agl::Shader>("assets/shaders/DefaultShader.glsl");

	// Scene manager initialization
	getInstance().s_sceneManager = std::make_unique<SceneManager>();
}

void AppData::terminate() {
	getInstance().s_window.reset();
	getInstance().s_globalShader.reset();
	getInstance().s_sceneManager.reset();
}

SceneManager& AppData::getSceneManager() {
	return *getInstance().s_sceneManager;
}

agl::Window& AppData::getWindow() {
	return *getInstance().s_window;
}

agl::Shader& AppData::getGlobalShader() {
	return *getInstance().s_globalShader;
}


}
