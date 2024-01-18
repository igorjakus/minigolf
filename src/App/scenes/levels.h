#pragma once

#include "../Core/SceneManager/Scene.h"
#include "Agl.h"
#include "../GUI.h"
#include "../ECS/Entity.h"


namespace golf {

	class LevelOneScene : public Scene {
	public:
		LevelOneScene();

		void update(float deltaT) override;
		void render() override;

	private:
		agl::Camera m_camera;
		agl::GraphicLayer m_graphicsLayer;
		GUILayer guiLayer;

		Entity wallA;
		Entity wallB;
		Entity frame1;
		Entity frame2;
		Entity frame3;
		Entity frame4;
		Entity pauseButton;
	};

	


	class LevelTwoScene : public Scene {
	public:
		LevelTwoScene();

		void update(float deltaT) override;
		void render() override;

	private:
		agl::Camera m_camera;
		agl::GraphicLayer m_graphicsLayer;

		std::unique_ptr<agl::Object> WallA;
		std::unique_ptr<agl::Object> WallB;
		std::unique_ptr<agl::Texture> WallTex;
		bool isFirstUpdate = true;
	};
}