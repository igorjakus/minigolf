#pragma once

#include "../Core/SceneManager/Scene.h"
#include "Agl.h"
#include "../GUI.h"
#include "../ECS/Entity.h"

namespace golf {
	class LevelSelectionScene : public Scene {
	public:
		LevelSelectionScene();

		void update(float deltaT) override;
		void render() override;

	private:
		agl::Camera m_camera;
		agl::GraphicLayer m_graphicsLayer;

		GUILayer guiLayer;
		Entity lvlOneButton;
		Entity lvlTwoButton;
		Entity lvlThreeButton;
		Entity lvlFourButton;
		Entity lvlFiveButton;

	};



	class ResultsScene : public Scene {
	public:
		ResultsScene(int score, int lvlNumber);

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