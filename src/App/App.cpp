#include "App.h"
#include "ImGui.h"

#include<dtl.h>
#include<pch.h>
#include<Window.h>
#include<Shader.h>

namespace golf {

const std::string App::c_defaultTitle = "Golf Game";

App::App(unsigned int width, unsigned int height, std::string title) 
	:window(width, height, title) {
	window.create();

	DTL_INF("Application created: {0}", window.getTitle());

	//////////////
	// Zdecydowanie do poprawy:
	int screenX = 0;
	int screenY = 0;
	window.getScreenResolution(screenX, screenY); 
	unsigned int windowPosX = static_cast<unsigned int>(screenX) / 2 - width / 2;
	unsigned int windowPosY = static_cast<unsigned int>(screenY) / 2 - height / 2;
	window.setWindowPos(windowPosX, windowPosY);
	//////////////

	window.setIcon("assets/icon/icon.png", "assets/icon/icon.png");

}

App::~App() = default;

void App::run() {

	DTL_INF("Application run: {0}", window.getTitle());

	while(!window.closeCallBack()) {

		IMGUI_NEW_FRAME;
		IMGUI_CALL(ImGui::ShowDemoWindow());

		window.FEP();
	}

	terminate();

}

void App::terminate() {

	DTL_INF("Application terminated: {0}", window.getTitle());

}

}
