#include "App.h"
#include<dtl.h>
#include<pch.h>
#include<ImGui.h>
#include<Window.h>
#include<Shader.h>

namespace golf {

const std::string App::c_defaultTitle = "Golf Game";

App::App(uint width, uint height, std::string title) 
	:window(width, height, title) {
	window.create();

	DTL_INF("Application created: {0}", window.getTitle());


	uint screenX = 0;
	uint screenY = 0;
	window.getScreenResolution(screenX, screenY); 
	const uint windowPosX = screenX / 2 - width / 2;
	const uint windowPosY = screenY / 2 - height / 2;
	window.setWindowPos(windowPosX, windowPosY);

	window.setIcon("assets/icon/icon.png", "assets/icon/icon.png");

}

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
