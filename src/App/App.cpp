#include"App.h"
#include "AppData.h"
#include "Scenes.h"
#include<dtl.h>
#include<pch.h>
#include<ImGui.h>
#include<Window.h>
#include<Shader.h>
#include<Agl.h>

namespace golf {



const std::string App::c_defaultTitle = "Golf Game";

App::App(uint width, uint height, const std::string& title)
	:m_title(title) {

	AppData::init(width, height, title);

	AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new BlankScene()));
	AppData::getSceneManager().loadNextScene();
	AppData::getSceneManager().nextScene();

	DTL_INF("Application created: {0}", title);

}

void App::run() {

	DTL_INF("Application run: {0}", m_title);

	while(!shouldClose()) {

		IMGUI_NEW_FRAME;
		IMGUI_CALL(ImGui::ShowDemoWindow());

		// TODO: better loop
		update(1);
		render();
	}

	terminate();

}

void App::update(float deltaT) {
	AppData::getSceneManager().update(deltaT);
}

void App::render() {
	AppData::getSceneManager().render();

	AppData::getWindow().FEP();
}

bool App::shouldClose() {
	return AppData::getWindow().closeCallBack();
}

void App::terminate() {

	DTL_INF("Application terminated: {0}", m_title);

}

}
