#include "AppData.h"

#include <dtl.h>



namespace golf {



AppData& AppData::getInstance() {
	static AppData instance;
	return instance;
}

void AppData::init(uint width, uint height, const std::string& title) {

	// Window creation
	getInstance().m_window = std::make_unique<agl::Window>(width, height, title);

	getInstance().m_window->create();

	glm::uvec2 screenRes = getInstance().m_window->getScreenResolution();
	const uint windowPosX = screenRes.x / 2 - width / 2;
	const uint windowPosY = screenRes.y / 2 - height / 2;
	getInstance().m_window->setWindowPos(windowPosX, windowPosY);

	getInstance().m_window->setIcon("assets/icon/icon.png", "assets/icon/icon.png");

	// Global shader creation
	getInstance().m_globalShader = std::make_unique<agl::Shader>("assets/shaders/DefaultShader.glsl");

	// Scene manager initialization
	getInstance().m_sceneManager = std::make_unique<SceneManager>();

	//Sus initialization
	getInstance().m_sus = std::make_unique<Sus>();

	// User input service initialization
	getInstance().m_input = std::make_unique<Input>();
	getInstance().m_input->setTargetWindow(*getInstance().m_window);
	getInstance().m_input->setCustomCursor();
}

void AppData::terminate() {
	glfwSetWindowUserPointer(getInstance().m_window->passPointer(), nullptr);
	getInstance().m_window.reset();
	getInstance().m_globalShader.reset();
	getInstance().m_sceneManager.reset();
	getInstance().m_sus.reset();
	getInstance().m_input.reset();
}

SceneManager& AppData::getSceneManager() {
	return *getInstance().m_sceneManager;
}

agl::Window& AppData::getWindow() {
	return *getInstance().m_window;
}

agl::Shader& AppData::getGlobalShader() {
	return *getInstance().m_globalShader;
}

Sus& AppData::getSus() {
	return *getInstance().m_sus;
}

Input& AppData::getInput() {
	return *getInstance().m_input;
}



}
