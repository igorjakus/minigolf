#pragma once

#include "../Core/SceneManager/Scene.h"
#include "Agl.h"
#include "../GUI.h"
#include "../ECS/Entity.h"
#include "App/Background.h"

namespace golf {
	class MainMenu : public Scene {
	public:
		MainMenu();

		void update(float deltaT) override;
		void render() override;

	private:
		agl::Camera m_camera;
		agl::GraphicLayer m_graphicsLayer;
		GUILayer guiLayer;
		Background background;

		Entity logo;
		Entity playButton;
		Entity howToGolfButton;
		Entity creditsButton;
		Entity exitButton;

	};

	class LevelSelectionScene : public Scene {
	public:
		LevelSelectionScene();

		void update(float deltaT) override;
		void render() override;

	private:
		agl::Camera m_camera;
		agl::GraphicLayer m_graphicsLayer;
		Background background;

		GUILayer guiLayer;
		Entity lvlOneButton;
		Entity lvlTwoButton;
		Entity lvlThreeButton;
		Entity lvlFourButton;
		Entity lvlFiveButton;

		Entity lvlOneStars;
		Entity lvlTwoStars;
		Entity lvlThreeStars;
		Entity lvlFourStars;
		Entity lvlFiveStars;

		Entity mainMenuButton;
	};

	class ResultsScene : public Scene {
	public:
		ResultsScene(int score,int stars, int lvlNumber);

		void update(float deltaT) override;
		void render() override;

	private:
		agl::Camera m_camera;
		agl::GraphicLayer m_graphicsLayer;
		[[maybe_unused]] int playerScore;
		int nrOfStars;
		int finishedLevelNumber;
		Background background;

		GUILayer guiLayer;
		Entity menuButton;
		Entity replayButton;
		Entity nextLevelButton;
		Entity starDisplay;
	};

	class CreditsScene : public Scene {
	public:
		CreditsScene();

		void update(float deltaT) override;
		void render() override;

	private:
		agl::Camera m_camera;
		agl::GraphicLayer m_graphicsLayer;
		Background background;

		GUILayer guiLayer;

		Entity creditsSheet;
		Entity mainMenuButton;
	};

	class HowToGolfScene : public Scene {
	public:
		HowToGolfScene();

		void update(float deltaT) override;
		void render() override;

	private:
		agl::Camera m_camera;
		agl::GraphicLayer m_graphicsLayer;
		Background background;

		GUILayer guiLayer;

		Entity tutorialSheet;
		Entity mainMenuButton;
	};

	class BlackScene : public Scene {
	public:
		BlackScene();

		void update(float deltaT) override;
		void render() override;

	private:
		agl::Camera m_camera;
		agl::GraphicLayer m_graphicsLayer;
		
		float m_timer = 1.f;
	};
}
