#include"App.h"
#include "AppData.h"
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

	DTL_INF("Application created: {0}", title);

}

void App::run() {

	DTL_INF("Application run: {0}", m_title);
	//temp
	agl::Shader shader("assets/shaders/DefaultShader.glsl");
	AGL_DEFINE_DEFTEX;

	while(shouldClose()) {

		IMGUI_NEW_FRAME;
		IMGUI_CALL(ImGui::ShowDemoWindow());

		AppData::Window().FEP();

	}

	terminate();

}

bool App::shouldClose() {
	return !AppData::Window().closeCallBack();
}

void App::terminate() {

	DTL_INF("Application terminated: {0}", m_title);

}

}
