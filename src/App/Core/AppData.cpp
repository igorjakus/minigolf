#include <pch.h>
#include "AppData.h"

#include "dtl.h"


namespace golf {


AppData& AppData::getInstance() {
	static AppData instance;
	return instance;
}

void AppData::init(uint width, uint height, const std::string& title) {
	DTL_ENT("===============================================================================");
	DTL_ENT("Application Systems initialization...");
	// Window creation
	getInstance().m_window = std::make_unique<agl::Window>(width, height, title);
	getInstance().m_window->create();

	agl::Shader::enableBlending();

	glm::uvec2 screenRes = getInstance().m_window->getScreenResolution();
	const uint windowPosX = screenRes.x / 2 - width / 2;
	const uint windowPosY = screenRes.y / 2 - height / 2;
	getInstance().m_window->setWindowPos(windowPosX, windowPosY);
	getInstance().m_window->setIcon("assets/icon/icon.png", "assets/icon/icon.png");
	DTL_INF("Window created");

	//Sus initialization
	getInstance().m_sus = std::make_unique<Sus>();
	DTL_ENT("Loading assets...");

	getInstance().m_sus->LoadListOfTextures({ "catcat.png", "sponge.png" }, 3, 3);
	getInstance().m_sus->LoadListOfTextures({ "Grass.png", "Wood.png" }, 1,1,GL_NEAREST, GL_REPEAT, GL_REPEAT);

	getInstance().m_sus->LoadAll();
	DTL_INF("Assets loaded");

	// Scene manager initialization
	getInstance().m_sceneManager = std::make_unique<SceneManager>();
	DTL_INF("Scene Manager created");

	// User input service initialization
	getInstance().m_input = std::make_unique<Input>();
	getInstance().m_input->setTargetWindow(*getInstance().m_window);
	getInstance().m_input->setCustomCursor();
	DTL_INF("User Input created");

	DTL_INF("Application systems initialized successfully");
	DTL_ENT("===============================================================================");
}

void AppData::terminate() {
	DTL_ENT("===============================================================================");
	DTL_ENT("Application systems termination...");
	glfwSetWindowUserPointer(getInstance().m_window->passPointer(), nullptr);
	getInstance().m_window.reset();
	getInstance().m_sceneManager.reset();
	AppData::getSus().UpdateSaveFile();
	getInstance().m_sus.reset();
	getInstance().m_input.reset();
	DTL_INF("Application systems terminated successfully");
	DTL_ENT("===============================================================================");
}

SceneManager& AppData::getSceneManager() {
	return *getInstance().m_sceneManager;
}

agl::Window& AppData::getWindow() {
	return *getInstance().m_window;
}

Sus& AppData::getSus() {
	return *getInstance().m_sus;
}

Input& AppData::getInput() {
	return *getInstance().m_input;
}



}
