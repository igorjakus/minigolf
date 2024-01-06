#include "App.h"

#include "Core/AppData.h"
#include "Scenes.h"

#include <Agl.h>
#include <chrono>
#include <dtl.h>
#include <ImGui.h>
#include <Window.h>
#include <Shader.h>
#include <pch.h>



namespace golf {



const std::string App::c_defaultTitle = "Golf Game";

App::App(uint width, uint height, const std::string& title)
	:m_title(title), m_updatesPerSecond(c_defaultUPS) {

	AppData::init(width, height, title);
	AppData::getSus().LoadListOfTextures({ "popcat.png","sponge.png" });
	AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new BlankScene()));
	AppData::getSceneManager().nextScene();

	DTL_INF("Application created: {0}", title);

}

void App::run() {

	DTL_INF("Application run: {0}", m_title);

	const double timePerUpdate = 1.0/m_updatesPerSecond;
	const auto deltaT = static_cast<float>(timePerUpdate);

	std::chrono::steady_clock::time_point lastFrameTime = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
	std::chrono::duration<double> timeBetweenFrames{};
	double lag = 0.0;

	while (!shouldClose()) 
	{
		now = std::chrono::steady_clock::now();
		timeBetweenFrames = std::chrono::duration_cast<std::chrono::duration<double>>(now - lastFrameTime);
		lastFrameTime = std::chrono::steady_clock::now();

		lag += timeBetweenFrames.count();

		while(lag >= timePerUpdate) {
			update(deltaT);
			lag -= timePerUpdate;
		}

		render();
	}

	terminate();

}

void App::update(float deltaT) {
	AppData::getSceneManager().update(deltaT);
}

void App::render() {
	IMGUI_NEW_FRAME;
	IMGUI_CALL(ImGui::ShowDemoWindow());
	AppData::getSceneManager().render();

	AppData::getInput().frameEnd();
	AppData::getWindow().FEP();
}

bool App::shouldClose() {
	return AppData::getWindow().closeCallBack();
}

void App::terminate() {

	AppData::terminate();

	DTL_INF("Application terminated: {0}", m_title);

}

}
