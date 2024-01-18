#include "pch.h"
#include "misc.h"
#include "../Graphics.h"
#include "levels.h"
#include "../Core/AppData.h"


namespace golf {

	using PositionType = GUIComponent::positionType;
	using ModeType = GUIComponent::modeType;

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
		AppData::getInput().attachCamera(&m_camera, 1.0f);
		lvlOneButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		lvlOneButton.getComponent<GUIComponent>()->setPosition(PositionType::TOPLEFT, 0.1f, -0.1f, ModeType::RELATIVE);
		lvlOneButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		lvlOneButton.getComponent<VisualComponent>()->setTexture("popcat");
		lvlOneButton.getTransform()->setScale(0.2f, 0.2f);
		lvlOneButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		lvlTwoButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		lvlTwoButton.getComponent<GUIComponent>()->setPosition(PositionType::TOPLEFT, 0.4f, -0.1f, ModeType::RELATIVE);
		lvlTwoButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		lvlTwoButton.getComponent<VisualComponent>()->setTexture("popcat");
		lvlTwoButton.getTransform()->setScale(0.2f, 0.2f);
		lvlTwoButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));


		lvlThreeButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		lvlThreeButton.getComponent<GUIComponent>()->setPosition(PositionType::TOPLEFT, 0.7f, -0.1f, ModeType::RELATIVE);
		lvlThreeButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		lvlThreeButton.getComponent<VisualComponent>()->setTexture("popcat");
		lvlThreeButton.getTransform()->setScale(0.2f, 0.2f);
		lvlThreeButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));


	}

	void LevelSelectionScene::update([[maybe_unused]] float deltaT)
	{
		auto ptr = lvlOneButton.getComponent<ButtonComponent>();
		ptr->update();
		if (ptr->isClicked()) {
			AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new LevelOneScene()));
			AppData::getSceneManager().nextScene();
		}
		if (ptr->isHovered()) {
			lvlOneButton.getComponent<VisualComponent>()->setTexture("sponge");
		}
		else { lvlOneButton.getComponent<VisualComponent>()->setTexture("popcat"); }

		ptr = lvlTwoButton.getComponent<ButtonComponent>();
		ptr->update();
		if (ptr->isHovered()) {
			lvlTwoButton.getComponent<VisualComponent>()->setTexture("sponge");
		}
		else { lvlTwoButton.getComponent<VisualComponent>()->setTexture("popcat"); }
		if (ptr->isClicked()) {
			AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new LevelTwoScene()));
			AppData::getSceneManager().nextScene();
			return;
		}

		ptr = lvlThreeButton.getComponent<ButtonComponent>();
		ptr->update();
		if (ptr->isHovered()) {
			lvlThreeButton.getComponent<VisualComponent>()->setTexture("sponge");
		}
		else { lvlThreeButton.getComponent<VisualComponent>()->setTexture("popcat"); }
		if (ptr->isClicked()) {
			AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new LevelThreeScene()));
			AppData::getSceneManager().nextScene();
			return;
		}
	}

	void LevelSelectionScene::render()
	{
		m_graphicsLayer.draw();
		guiLayer.render();
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