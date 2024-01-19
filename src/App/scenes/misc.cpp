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
	//================================
	//MainMenu
	//================================
	MainMenu::MainMenu()
		:m_graphicsLayer(*AppData::getSus().GetShader("DefaultShader.glsl"), m_camera)
	{
		AppData::getInput().attachCamera(&m_camera, 1.0f);
		playButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		playButton.getComponent<GUIComponent>()->setPosition(PositionType::CENTER,0.0f,0.0f, ModeType::RELATIVE);
		playButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		playButton.getComponent<VisualComponent>()->setTexture("play_not_pressed");
		playButton.getTransform()->setScale(0.34f, 0.22f);
		playButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

	}
	void MainMenu::update([[maybe_unused]] float deltaT) {

		auto ptr = playButton.getComponent<ButtonComponent>();
		ptr->update();


		if (ptr->isClicked()) {
			AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new LevelSelectionScene()));
			AppData::getSceneManager().nextScene();
		}
		if (ptr->isHovered()) {
			playButton.getComponent<VisualComponent>()->setTexture("play_pressed");
		}
		else { playButton.getComponent<VisualComponent>()->setTexture("play_not_pressed"); }
		
	}
	void MainMenu::render()
	{
		m_graphicsLayer.draw();
		guiLayer.render();
	}


	// ===============================
	// LevelSelectionScene
	// ===============================

	LevelSelectionScene::LevelSelectionScene()
		:m_graphicsLayer(*AppData::getSus().GetShader("DefaultShader.glsl"), m_camera)
	{
		AppData::getInput().attachCamera(&m_camera, 1.0f);
		lvlOneButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		lvlOneButton.getComponent<GUIComponent>()->setPosition(PositionType::CENTER, -0.3f, 0.3f, ModeType::RELATIVE);
		lvlOneButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		lvlOneButton.getComponent<VisualComponent>()->setTexture("1_not_pressed");
		lvlOneButton.getTransform()->setScale(0.2f, 0.2f);
		lvlOneButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		lvlTwoButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		lvlTwoButton.getComponent<GUIComponent>()->setPosition(PositionType::CENTER, 0.0f, 0.3f, ModeType::RELATIVE);
		lvlTwoButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		lvlTwoButton.getComponent<VisualComponent>()->setTexture("2_not_pressed");
		lvlTwoButton.getTransform()->setScale(0.2f, 0.2f);
		lvlTwoButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));


		lvlThreeButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		lvlThreeButton.getComponent<GUIComponent>()->setPosition(PositionType::CENTER, 0.3f, 0.3f, ModeType::RELATIVE);
		lvlThreeButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		lvlThreeButton.getComponent<VisualComponent>()->setTexture("3_not_pressed");
		lvlThreeButton.getTransform()->setScale(0.2f, 0.2f);
		lvlThreeButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		lvlFourButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		lvlFourButton.getComponent<GUIComponent>()->setPosition(PositionType::CENTER, -0.3f, 0.0f, ModeType::RELATIVE);
		lvlFourButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		lvlFourButton.getComponent<VisualComponent>()->setTexture("4_not_pressed");
		lvlFourButton.getTransform()->setScale(0.2f, 0.2f);
		lvlFourButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		lvlFiveButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		lvlFiveButton.getComponent<GUIComponent>()->setPosition(PositionType::CENTER, -0.0f, 0.0f, ModeType::RELATIVE);
		lvlFiveButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		lvlFiveButton.getComponent<VisualComponent>()->setTexture("5_not_pressed");
		lvlFiveButton.getTransform()->setScale(0.2f, 0.2f);
		lvlFiveButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

	}

	void LevelSelectionScene::update([[maybe_unused]] float deltaT)
	{




		auto ptr = lvlOneButton.getComponent<ButtonComponent>();
		ptr->update();
		
		if (AppData::getSus().IsUnlocked(1)) {
			if (ptr->isClicked()) {
				AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new LevelOneScene()));
				AppData::getSceneManager().nextScene();
			}
			if (ptr->isHovered()) {
				lvlOneButton.getComponent<VisualComponent>()->setTexture("1_pressed");
			}
			else { lvlOneButton.getComponent<VisualComponent>()->setTexture("1_not_pressed"); }
		}
		else { lvlOneButton.getComponent<VisualComponent>()->setTexture("level_locked"); }

		ptr = lvlTwoButton.getComponent<ButtonComponent>();
		ptr->update();
		if (AppData::getSus().IsUnlocked(2)) {
			if (ptr->isHovered()) {
				lvlTwoButton.getComponent<VisualComponent>()->setTexture("2_pressed");
			}
			else { lvlTwoButton.getComponent<VisualComponent>()->setTexture("2_not_pressed"); }
			if (ptr->isClicked()) {
				AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new LevelTwoScene()));
				AppData::getSceneManager().nextScene();
				return;
			}
		}
		else { lvlTwoButton.getComponent<VisualComponent>()->setTexture("level_locked"); }

		ptr = lvlThreeButton.getComponent<ButtonComponent>();
		ptr->update();
		if (AppData::getSus().IsUnlocked(3)) {
			if (ptr->isHovered()) {
				lvlThreeButton.getComponent<VisualComponent>()->setTexture("3_pressed");
			}
			else { lvlThreeButton.getComponent<VisualComponent>()->setTexture("3_not_pressed"); }
			if (ptr->isClicked()) {
				AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new LevelThreeScene()));
				AppData::getSceneManager().nextScene();
				return;
			}
		}
		else { lvlThreeButton.getComponent<VisualComponent>()->setTexture("level_locked"); }

		ptr = lvlFourButton.getComponent<ButtonComponent>();
		ptr->update();
		if (AppData::getSus().IsUnlocked(4)) {
			if (ptr->isHovered()) {
				lvlFourButton.getComponent<VisualComponent>()->setTexture("4_pressed");
			}
			else { lvlFourButton.getComponent<VisualComponent>()->setTexture("4_not_pressed"); }
			if (ptr->isClicked()) {
				AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new LevelFourScene()));
				AppData::getSceneManager().nextScene();
				return;
			}
		}
		else { lvlFourButton.getComponent<VisualComponent>()->setTexture("level_locked"); }

		ptr = lvlFiveButton.getComponent<ButtonComponent>();
		ptr->update();
		if (AppData::getSus().IsUnlocked(5)) {
			if (ptr->isHovered()) {
				lvlFiveButton.getComponent<VisualComponent>()->setTexture("5_pressed");
			}
			else { lvlFiveButton.getComponent<VisualComponent>()->setTexture("5_not_pressed"); }
			if (ptr->isClicked()) {
				AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new LevelFiveScene()));
				AppData::getSceneManager().nextScene();
				return;
			}
		}
		else { lvlFiveButton.getComponent<VisualComponent>()->setTexture("level_locked"); }

	}

	void LevelSelectionScene::render()
	{
		m_graphicsLayer.draw();
		guiLayer.render();
	}



	ResultsScene::ResultsScene(int score, int lvlNumber)
		:m_graphicsLayer(*AppData::getSus().GetShader("DefaultShader.glsl"), m_camera), playerScore(score), finishedLevelNumber(lvlNumber)
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