#include"App.h"
#include<dtl.h>
#include<pch.h>
#include<ImGui.h>
#include<Window.h>
#include<Shader.h>
#include<Agl.h>

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
	//temp
	agl::Shader shader("assets/shaders/DefaultShader.glsl");
	glm::mat4 proj = glm::ortho(0.0f, 640.f, 0.0f, 480.f, -1.0f, 1.0f);
	shader.setUniformMatrix4("u_P", proj);
	AGL_DEFINE_DEFTEX;
	agl::GraphicLayer r(&shader);
	agl::Object o(25, 25, AGL_DEFTEX, { 50, 50 });
	r.addObject(o);

	while(!window.closeCallBack()) {

		if (window.IsKeyPressed(GLFW_KEY_E)) { o.setRotation(o.getRotation() - 1); }
		if (window.IsKeyPressed(GLFW_KEY_Q)) { o.setRotation(o.getRotation() + 1); }
		if (window.IsKeyPressed(GLFW_KEY_W)) { o.setPosition(o.getPosition() + glm::vec2{0.f, 1.f }); }
		if (window.IsKeyPressed(GLFW_KEY_S)) { o.setPosition(o.getPosition() + glm::vec2{0.f, -1.f }); }
		if (window.IsKeyPressed(GLFW_KEY_D)) { o.setPosition(o.getPosition() + glm::vec2{1.f, 0.f }); }
		if (window.IsKeyPressed(GLFW_KEY_A)) { o.setPosition(o.getPosition() + glm::vec2{-1.f, 0.f }); }
		if (window.IsKeyPressed(GLFW_KEY_UP)) { o.setScale(o.getScale().x + 1, o.getScale().y); }
		if (window.IsKeyPressed(GLFW_KEY_RIGHT)) { o.setScale(o.getScale().x, o.getScale().y + 1); }
		if (window.IsKeyPressed(GLFW_KEY_DOWN)) { o.setScale(o.getScale().x - 1, o.getScale().y); }
		if (window.IsKeyPressed(GLFW_KEY_LEFT)) { o.setScale(o.getScale().x, o.getScale().y - 1); }

		r.draw();




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
