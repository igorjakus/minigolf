#pragma once

#include "../Core/SceneManager/Scene.h"
#include "Agl.h"
#include "../GUI.h"
#include "../ECS/Entity.h"

namespace golf {
	class LevelSelectionScene : public Scene {
	public:
		LevelSelectionScene();
		~LevelSelectionScene() override = default;
		LevelSelectionScene(LevelSelectionScene&&) = delete;
		LevelSelectionScene(const LevelSelectionScene&) = delete;
		LevelSelectionScene& operator=(LevelSelectionScene&&) = delete;
		LevelSelectionScene& operator=(const LevelSelectionScene&) = delete;

		void update(float deltaT) override;
		void render() override;

	private:
		agl::Camera m_camera;
		agl::GraphicLayer m_graphicsLayer;

		std::unique_ptr<agl::Object> cokolwiek;
		bool isFirstUpdate = true;

	};



	class ResultsScene : public Scene {
	public:
		ResultsScene(int score, int lvlNumber);
		~ResultsScene() override = default;
		ResultsScene(ResultsScene&&) = delete;
		ResultsScene(const ResultsScene&) = delete;
		ResultsScene& operator=(ResultsScene&&) = delete;
		ResultsScene& operator=(const ResultsScene&) = delete;

		void update(float deltaT) override;
		void render() override;

	private:
		agl::Camera m_camera;
		agl::GraphicLayer m_graphicsLayer;
		[[maybe_unused]] int playerScore;
		bool isFirstUpdate = true;
		int finishedLevelNumber;
	};
}