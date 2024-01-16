#include "pch.h"
#include "misc.h"
#include "../Graphics.h"
#include "levels.h"
#include "../Core/AppData.h"


namespace golf {


	//funkcja ktora uruchamia odpowiedni poziom
	void startLevel(int levelNumber)
	{
		if (levelNumber == 1) {
			AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new LevelOneScene()));
			AppData::getSceneManager().nextScene();
		}
		if (levelNumber == 2) {
			AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new LevelTwoScene()));
			AppData::getSceneManager().nextScene();
		}
	}


	// ===============================
	// LevelSelectionScene
	// ===============================

	LevelSelectionScene::LevelSelectionScene()
		:m_camera(0.F, 0.F, 1.F, 1.F, 1.F),
		m_graphicsLayer(*AppData::getSus().GetShader("DefaultShader.glsl"), m_camera)
	{
		const uint tempX = AppData::getWindow().getWindowSize().x;
		const uint tempY = AppData::getWindow().getWindowSize().y;
		m_camera.setSize(static_cast<float>(tempX) / static_cast<float>(tempY), 1.0F);
	}

	void LevelSelectionScene::update([[maybe_unused]] float deltaT)
	{
		if (isFirstUpdate) {
			DTL_INF("level selection scene -- click 1 to play lvl 1, 2 to play lvl 2");
			isFirstUpdate = false;
		}


		if (AppData::getInput().isKeyClicked("1")) {
			AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new LevelOneScene()));
			AppData::getSceneManager().nextScene();
		}

		if (AppData::getInput().isKeyClicked("2")) {
			AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new LevelTwoScene()));
			AppData::getSceneManager().nextScene();
		}
	}

	void LevelSelectionScene::render()
	{
		m_graphicsLayer.draw();
	}



	ResultsScene::ResultsScene(int score, int lvlNumber)
		:m_camera(0.F, 0.F, 1.F, 1.F, 1.F),
		m_graphicsLayer(*AppData::getSus().GetShader("DefaultShader.glsl"), m_camera), playerScore(score), finishedLevelNumber(lvlNumber)
	{
		const float tempX = static_cast<float>(AppData::getWindow().getWindowSize().x);
		const float tempY = static_cast<float>(AppData::getWindow().getWindowSize().y);
		m_camera.setSize(tempX / tempY, 1.0f);
	}

	void ResultsScene::update([[maybe_unused]] float deltaT)
	{
		if (isFirstUpdate) {
			DTL_INF("results scene -- click q to quit, r to play again, c to continue (next lvl)");
			isFirstUpdate = false;
		}

		//quit
		if (AppData::getInput().isKeyClicked("Q")) {
			AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new LevelSelectionScene()));
			AppData::getSceneManager().nextScene();
		}

		//play again
		if (AppData::getInput().isKeyClicked("R")) {
			startLevel(finishedLevelNumber);
		}

		//next level

		if (AppData::getInput().isKeyClicked("C")) {
			startLevel(finishedLevelNumber + 1);
		}


	}

	void ResultsScene::render()
	{
		m_graphicsLayer.draw();
	}


}