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

		Entity wallA;
		Entity wallB;
		bool isFirstUpdate = true;
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