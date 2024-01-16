#pragma once

#include "../Core/SceneManager/Scene.h"
#include "Agl.h"
#include "../GUI.h"
#include "../ECS/Entity.h"


namespace golf {

	class LevelOneScene : public Scene {
	public:
		LevelOneScene();
		~LevelOneScene() override = default;
		LevelOneScene(LevelOneScene&&) = delete;
		LevelOneScene(const LevelOneScene&) = delete;
		LevelOneScene& operator=(LevelOneScene&&) = delete;
		LevelOneScene& operator=(const LevelOneScene&) = delete;

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
		~LevelTwoScene() override = default;
		LevelTwoScene(LevelTwoScene&&) = delete;
		LevelTwoScene(const LevelTwoScene&) = delete;
		LevelTwoScene& operator=(LevelTwoScene&&) = delete;
		LevelTwoScene& operator=(const LevelTwoScene&) = delete;

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