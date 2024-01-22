#include "pch.h"
#include "misc.h"
#include "levels.h"
#include "transition.h"
#include "../Graphics.h"
#include "../Core/AppData.h"


//NOLINTBEGIN(readability-function-cognitive-complexity)

namespace golf {

	using PositionType = GUIComponent::positionType;
	using ModeType = GUIComponent::modeType;

	//funkcja ktora uruchamia odpowiedni poziom
	void startLevel(int levelNumber, std::shared_ptr<Scene> thisScene)
	{
		if (levelNumber == 1) {
			auto next = std::shared_ptr<Scene>(new LevelOneScene());
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(thisScene, next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
		}
		if (levelNumber == 2) {
			auto next = std::shared_ptr<Scene>(new LevelTwoScene());
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(thisScene, next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
		}
		if (levelNumber == 3) {
			auto next = std::shared_ptr<Scene>(new LevelThreeScene());
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(thisScene, next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
		}
		if (levelNumber == 4) {
			auto next = std::shared_ptr<Scene>(new LevelFourScene());
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(thisScene, next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
		}
		if (levelNumber == 5) {
			auto next = std::shared_ptr<Scene>(new LevelFiveScene());
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(thisScene, next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
		}

		if (levelNumber == 6) {
			auto next = std::shared_ptr<Scene>(new LevelSixScene());
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(thisScene, next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
		}
		if (levelNumber == 7) {
			auto next = std::shared_ptr<Scene>(new EndScreen());
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(thisScene, next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
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

		

		logo.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		logo.getComponent<GUIComponent>()->setPosition(PositionType::CENTER, 0.0f, 0.25f, ModeType::RELATIVE);
		logo.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		logo.getComponent<VisualComponent>()->setTexture("golf_logo");
		logo.getTransform()->setScale(0.82f, 0.41f);

		playButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		playButton.getComponent<GUIComponent>()->setPosition(PositionType::CENTER,0.0f,-0.1f, ModeType::RELATIVE);
		playButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		playButton.getComponent<VisualComponent>()->setTexture("play_not_pressed");
		playButton.getTransform()->setScale(0.28f, 0.18f);
		playButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		howToGolfButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		howToGolfButton.getComponent<GUIComponent>()->setPosition(PositionType::CENTER, 0.0f, -0.25f, ModeType::RELATIVE);
		howToGolfButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		howToGolfButton.getComponent<VisualComponent>()->setTexture("how_to_golf_not_pressed");
		howToGolfButton.getTransform()->setScale(0.48f, 0.11f);
		howToGolfButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		creditsButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		creditsButton.getComponent<GUIComponent>()->setPosition(PositionType::CENTER, 0.0f, -0.37f, ModeType::RELATIVE);
		creditsButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		creditsButton.getComponent<VisualComponent>()->setTexture("credits_not_pressed");
		creditsButton.getTransform()->setScale(0.28f, 0.11f);
		creditsButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		exitButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		exitButton.getComponent<GUIComponent>()->setPosition(PositionType::BOTTOMLEFT, 0.03f, 0.03f, ModeType::RELATIVE);
		exitButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		exitButton.getComponent<VisualComponent>()->setTexture("exit_not_pressed");
		exitButton.getTransform()->setScale(0.12f, 0.12f);
		exitButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));
	}
	void MainMenu::update([[maybe_unused]] float deltaT) {


		auto ptr = playButton.getComponent<ButtonComponent>();
		ptr->update();
		if (ptr->isClicked()) {
			auto next = std::shared_ptr<Scene>(new LevelSelectionScene());
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(shared_from_this(), next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
		}
		if (ptr->isHovered()) {
			playButton.getComponent<VisualComponent>()->setTexture("play_pressed");
		}
		else { playButton.getComponent<VisualComponent>()->setTexture("play_not_pressed"); }

		ptr = howToGolfButton.getComponent<ButtonComponent>();
		ptr->update();
		if (ptr->isClicked()) {
			auto next = std::shared_ptr<Scene>(new HowToGolfScene());
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(shared_from_this(), next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
		}
		if (ptr->isHovered()) {
			howToGolfButton.getComponent<VisualComponent>()->setTexture("how_to_golf_pressed");
		}
		else { howToGolfButton.getComponent<VisualComponent>()->setTexture("how_to_golf_not_pressed"); }

		ptr = creditsButton.getComponent<ButtonComponent>();
		ptr->update();
		if (ptr->isClicked()) {
			auto next = std::shared_ptr<Scene>(new CreditsScene());
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(shared_from_this(), next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
		}
		if (ptr->isHovered()) {
			creditsButton.getComponent<VisualComponent>()->setTexture("credits_pressed");
		}
		else { creditsButton.getComponent<VisualComponent>()->setTexture("credits_not_pressed"); }

		ptr = exitButton.getComponent<ButtonComponent>();
		ptr->update();
		if (ptr->isClicked()) {
			AppData::getWindow().close();
		}
		if (ptr->isHovered()) {
			exitButton.getComponent<VisualComponent>()->setTexture("exit_pressed");
		}
		else { exitButton.getComponent<VisualComponent>()->setTexture("exit_not_pressed"); }
		
	}
	void MainMenu::render()
	{
		background.render();
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
		lvlOneButton.getComponent<GUIComponent>()->setPosition(PositionType::CENTER, -0.4f, 0.3f, ModeType::RELATIVE);
		lvlOneButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		lvlOneButton.getComponent<VisualComponent>()->setTexture("1_not_pressed");
		lvlOneButton.getTransform()->setScale(0.2f, 0.2f);
		lvlOneButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		//mo¿e: sprawdza przy gwiazdkach czy zablokowany
		//==Level 1
		lvlOneStars.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		lvlOneStars.getComponent<GUIComponent>()->setPosition(PositionType::CENTER, -0.4f, 0.2f, ModeType::RELATIVE);
		lvlOneStars.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		if (AppData::getSus().StarCount(1) == 3) {
			lvlOneStars.getComponent<VisualComponent>()->setTexture("stars_3");
		}
		if (AppData::getSus().StarCount(1) == 2) {
			lvlOneStars.getComponent<VisualComponent>()->setTexture("stars_2");
		}
		if (AppData::getSus().StarCount(1) == 1) {
			lvlOneStars.getComponent<VisualComponent>()->setTexture("stars_1");
		}
		if (AppData::getSus().StarCount(1) == 0) {
			lvlOneStars.getComponent<VisualComponent>()->setTexture("stars_0");
		}
		lvlOneStars.getTransform()->setScale(0.295f, 0.095f);

		//==Level 2
		lvlTwoButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		lvlTwoButton.getComponent<GUIComponent>()->setPosition(PositionType::CENTER, 0.0f, 0.3f, ModeType::RELATIVE);
		lvlTwoButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		lvlTwoButton.getComponent<VisualComponent>()->setTexture("2_not_pressed");
		lvlTwoButton.getTransform()->setScale(0.2f, 0.2f);
		lvlTwoButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		lvlTwoStars.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		lvlTwoStars.getComponent<GUIComponent>()->setPosition(PositionType::CENTER, 0.0f, 0.2f, ModeType::RELATIVE);
		lvlTwoStars.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		if (AppData::getSus().StarCount(2) == 3) {
			lvlTwoStars.getComponent<VisualComponent>()->setTexture("stars_3");
		}
		if (AppData::getSus().StarCount(2) == 2) {
			lvlTwoStars.getComponent<VisualComponent>()->setTexture("stars_2");
		}
		if (AppData::getSus().StarCount(2) == 1) {
			lvlTwoStars.getComponent<VisualComponent>()->setTexture("stars_1");
		}
		if (AppData::getSus().StarCount(2) == 0) {
			lvlTwoStars.getComponent<VisualComponent>()->setTexture("stars_0");
		}
		lvlTwoStars.getTransform()->setScale(0.295f, 0.095f);

		//==Level 3
		lvlThreeButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		lvlThreeButton.getComponent<GUIComponent>()->setPosition(PositionType::CENTER, 0.4f, 0.3f, ModeType::RELATIVE);
		lvlThreeButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		lvlThreeButton.getComponent<VisualComponent>()->setTexture("3_not_pressed");
		lvlThreeButton.getTransform()->setScale(0.2f, 0.2f);
		lvlThreeButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		lvlThreeStars.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		lvlThreeStars.getComponent<GUIComponent>()->setPosition(PositionType::CENTER, 0.4f, 0.2f, ModeType::RELATIVE);
		lvlThreeStars.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		if (AppData::getSus().StarCount(3) == 3) {
			lvlThreeStars.getComponent<VisualComponent>()->setTexture("stars_3");
		}
		if (AppData::getSus().StarCount(3) == 2) {
			lvlThreeStars.getComponent<VisualComponent>()->setTexture("stars_2");
		}
		if (AppData::getSus().StarCount(3) == 1) {
			lvlThreeStars.getComponent<VisualComponent>()->setTexture("stars_1");
		}
		if (AppData::getSus().StarCount(3) == 0) {
			lvlThreeStars.getComponent<VisualComponent>()->setTexture("stars_0");
		}
		lvlThreeStars.getTransform()->setScale(0.295f, 0.095f);

		//===Level 4
		lvlFourButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		lvlFourButton.getComponent<GUIComponent>()->setPosition(PositionType::CENTER, -0.4f, 0.0f, ModeType::RELATIVE);
		lvlFourButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		lvlFourButton.getComponent<VisualComponent>()->setTexture("4_not_pressed");
		lvlFourButton.getTransform()->setScale(0.2f, 0.2f);
		lvlFourButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		lvlFourStars.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		lvlFourStars.getComponent<GUIComponent>()->setPosition(PositionType::CENTER, -0.4f, -0.1f, ModeType::RELATIVE);
		lvlFourStars.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		if (AppData::getSus().StarCount(4) == 3) {
			lvlFourStars.getComponent<VisualComponent>()->setTexture("stars_3");
		}
		if (AppData::getSus().StarCount(4) == 2) {
			lvlFourStars.getComponent<VisualComponent>()->setTexture("stars_2");
		}
		if (AppData::getSus().StarCount(4) == 1) {
			lvlFourStars.getComponent<VisualComponent>()->setTexture("stars_1");
		}
		if (AppData::getSus().StarCount(4) == 0) {
			lvlFourStars.getComponent<VisualComponent>()->setTexture("stars_0");
		}
		lvlFourStars.getTransform()->setScale(0.295f, 0.095f);

		//===Level 5
		lvlFiveButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		lvlFiveButton.getComponent<GUIComponent>()->setPosition(PositionType::CENTER, 0.0f, 0.0f, ModeType::RELATIVE);
		lvlFiveButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		lvlFiveButton.getComponent<VisualComponent>()->setTexture("5_not_pressed");
		lvlFiveButton.getTransform()->setScale(0.2f, 0.2f);
		lvlFiveButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		lvlFiveStars.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		lvlFiveStars.getComponent<GUIComponent>()->setPosition(PositionType::CENTER, 0.0f, -0.1f, ModeType::RELATIVE);
		lvlFiveStars.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		if (AppData::getSus().StarCount(5) == 3) {
			lvlFiveStars.getComponent<VisualComponent>()->setTexture("stars_3");
		}
		if (AppData::getSus().StarCount(5) == 2) {
			lvlFiveStars.getComponent<VisualComponent>()->setTexture("stars_2");
		}
		if (AppData::getSus().StarCount(5) == 1) {
			lvlFiveStars.getComponent<VisualComponent>()->setTexture("stars_1");
		}
		if (AppData::getSus().StarCount(5) == 0) {
			lvlFiveStars.getComponent<VisualComponent>()->setTexture("stars_0");
		}
		lvlFiveStars.getTransform()->setScale(0.295f, 0.095f);

		//==Level 6
		lvlSixButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		lvlSixButton.getComponent<GUIComponent>()->setPosition(PositionType::CENTER, 0.4f, 0.0f, ModeType::RELATIVE);
		lvlSixButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		lvlSixButton.getComponent<VisualComponent>()->setTexture("2_not_pressed");
		lvlSixButton.getTransform()->setScale(0.2f, 0.2f);
		lvlSixButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		lvlSixStars.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		lvlSixStars.getComponent<GUIComponent>()->setPosition(PositionType::CENTER, 0.4f, -0.1f, ModeType::RELATIVE);
		lvlSixStars.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		if (AppData::getSus().StarCount(2) == 3) {
			lvlSixStars.getComponent<VisualComponent>()->setTexture("stars_3");
		}
		if (AppData::getSus().StarCount(2) == 2) {
			lvlSixStars.getComponent<VisualComponent>()->setTexture("stars_2");
		}
		if (AppData::getSus().StarCount(2) == 1) {
			lvlSixStars.getComponent<VisualComponent>()->setTexture("stars_1");
		}
		if (AppData::getSus().StarCount(2) == 0) {
			lvlSixStars.getComponent<VisualComponent>()->setTexture("stars_0");
		}
		lvlSixStars.getTransform()->setScale(0.295f, 0.095f);
		//===main Menu button:
		mainMenuButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		mainMenuButton.getComponent<GUIComponent>()->setPosition(PositionType::BOTTOMLEFT, 0.03f, 0.03f, ModeType::RELATIVE);
		mainMenuButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		mainMenuButton.getComponent<VisualComponent>()->setTexture("return_not_pressed");
		mainMenuButton.getTransform()->setScale(0.12f, 0.12f);
		mainMenuButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));
	}

	void LevelSelectionScene::update([[maybe_unused]] float deltaT)
	{
		auto ptr = lvlOneButton.getComponent<ButtonComponent>();
		ptr->update();
		
		if (AppData::getSus().IsUnlocked(1)) {
			if (ptr->isClicked()) {
				startLevel(1, shared_from_this());
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
				startLevel(2, shared_from_this());
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
				startLevel(3, shared_from_this());
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
				startLevel(4, shared_from_this());
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
				startLevel(5, shared_from_this());
				return;
			}
		}
		else { lvlFiveButton.getComponent<VisualComponent>()->setTexture("level_locked"); }


		ptr = lvlSixButton.getComponent<ButtonComponent>();
		ptr->update();
		if (AppData::getSus().IsUnlocked(6)) {
			if (ptr->isHovered()) {
				lvlSixButton.getComponent<VisualComponent>()->setTexture("6_pressed");
			}
			else { lvlSixButton.getComponent<VisualComponent>()->setTexture("6_not_pressed"); }
			if (ptr->isClicked()) {
				startLevel(6, shared_from_this());
				return;
			}
		}
		else { lvlSixButton.getComponent<VisualComponent>()->setTexture("level_locked"); }



		ptr = mainMenuButton.getComponent<ButtonComponent>();
		ptr->update();

		if (ptr->isHovered()) {
			mainMenuButton.getComponent<VisualComponent>()->setTexture("return_pressed");
		}
		else { mainMenuButton.getComponent<VisualComponent>()->setTexture("return_not_pressed"); }
		if (ptr->isClicked()) {
			auto next = std::shared_ptr<Scene>(new MainMenu());
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(shared_from_this(), next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
			return;
		}
		

	}

	void LevelSelectionScene::render()
	{
		background.render();
		m_graphicsLayer.draw();
		guiLayer.render();
	}



	ResultsScene::ResultsScene(int score, int stars, int lvlNumber)
		:m_graphicsLayer(*AppData::getSus().GetShader("DefaultShader.glsl"), m_camera), playerScore(score), nrOfStars(stars), finishedLevelNumber(lvlNumber)
	{

		AppData::getInput().attachCamera(&m_camera, 1.0f);

		menuButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		menuButton.getComponent<GUIComponent>()->setPosition(PositionType::CENTER, -0.5f, -0.3f, ModeType::RELATIVE);
		menuButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		menuButton.getComponent<VisualComponent>()->setTexture("menu_not_pressed");
		menuButton.getTransform()->setScale(0.2f, 0.2f);
		menuButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		replayButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		replayButton.getComponent<GUIComponent>()->setPosition(PositionType::CENTER, 0.0f, -0.3f, ModeType::RELATIVE);
		replayButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		replayButton.getComponent<VisualComponent>()->setTexture("replay_not_pressed");
		replayButton.getTransform()->setScale(0.2f, 0.2f);
		replayButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		nextLevelButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		nextLevelButton.getComponent<GUIComponent>()->setPosition(PositionType::CENTER, 0.5f, -0.3f, ModeType::RELATIVE);
		nextLevelButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		nextLevelButton.getComponent<VisualComponent>()->setTexture("next_not_pressed");
		nextLevelButton.getTransform()->setScale(0.2f, 0.2f);
		nextLevelButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		starDisplay.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		starDisplay.getComponent<GUIComponent>()->setPosition(PositionType::CENTER, 0.0f, 0.1f, ModeType::RELATIVE);
		starDisplay.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		starDisplay.getTransform()->setScale(1.02f, 0.38f);
		if (stars == 3) {
			starDisplay.getComponent<VisualComponent>()->setTexture("stars_3");
		}
		if (stars == 2) {
			starDisplay.getComponent<VisualComponent>()->setTexture("stars_2");
		}
		if (stars == 1) {
			starDisplay.getComponent<VisualComponent>()->setTexture("stars_1");
		}
		if (stars == 0) {
			starDisplay.getComponent<VisualComponent>()->setTexture("stars_0");
		}

		if (playerScore < AppData::getSus().HighScore(finishedLevelNumber) || AppData::getSus().HighScore(finishedLevelNumber) == 0) {
			AppData::getSus().ChangeHighScore(finishedLevelNumber, playerScore);
		}
		if (nrOfStars > AppData::getSus().StarCount(finishedLevelNumber)) {
			AppData::getSus().ChangeStars(finishedLevelNumber, nrOfStars);
		}
		AppData::getSus().Unlock(finishedLevelNumber + 1);

		AppData::getAudio().playSound("win-trabka");
	}

	void ResultsScene::update([[maybe_unused]] float deltaT)
	{
		//quit
		auto ptr = menuButton.getComponent<ButtonComponent>();
		ptr->update();
		if (ptr->isClicked()) {
			auto next = std::shared_ptr<Scene>(new LevelSelectionScene());
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(shared_from_this(), next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
		}
		if (ptr->isHovered()) {
			menuButton.getComponent<VisualComponent>()->setTexture("menu_pressed");
		}
		else { menuButton.getComponent<VisualComponent>()->setTexture("menu_not_pressed"); }


		//play again
		ptr = replayButton.getComponent<ButtonComponent>();
		ptr->update();
		if (ptr->isClicked()) {
			startLevel(finishedLevelNumber, shared_from_this());
		}
		if (ptr->isHovered()) {
			replayButton.getComponent<VisualComponent>()->setTexture("replay_pressed");
		}
		else { replayButton.getComponent<VisualComponent>()->setTexture("replay_not_pressed"); }

		//next level
		ptr = nextLevelButton.getComponent<ButtonComponent>();
		ptr->update();
		if (ptr->isClicked()) {
			startLevel(finishedLevelNumber + 1, shared_from_this());
		}
		if (ptr->isHovered()) {
			nextLevelButton.getComponent<VisualComponent>()->setTexture("next_pressed");
		}
		else { nextLevelButton.getComponent<VisualComponent>()->setTexture("next_not_pressed"); }


	}

	void ResultsScene::render()
	{
		background.render();
		m_graphicsLayer.draw();
		guiLayer.render();
	}

	CreditsScene::CreditsScene() 
		:m_graphicsLayer(*AppData::getSus().GetShader("DefaultShader.glsl"), m_camera) {

		//===Credits Sheet:
		creditsSheet.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		creditsSheet.getComponent<GUIComponent>()->setPosition(PositionType::CENTER, 0.0f, 0.0f, ModeType::RELATIVE);
		creditsSheet.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		creditsSheet.getComponent<VisualComponent>()->setTexture("credits");
		creditsSheet.getTransform()->setScale(0.844f, 0.718f);

		//===main Menu button:
		mainMenuButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		mainMenuButton.getComponent<GUIComponent>()->setPosition(PositionType::BOTTOMLEFT, 0.03f, 0.03f, ModeType::RELATIVE);
		mainMenuButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		mainMenuButton.getComponent<VisualComponent>()->setTexture("return_not_pressed");
		mainMenuButton.getTransform()->setScale(0.12f, 0.12f);
		mainMenuButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));
	}
	void CreditsScene::update([[maybe_unused]] float deltaT) {
		auto ptr = mainMenuButton.getComponent<ButtonComponent>();
		ptr->update();
		if (ptr->isClicked()) {
			auto next = std::shared_ptr<Scene>(new MainMenu());
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(shared_from_this(), next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
		}
		if (ptr->isHovered()) {
			mainMenuButton.getComponent<VisualComponent>()->setTexture("return_pressed");
		}
		else { mainMenuButton.getComponent<VisualComponent>()->setTexture("return_not_pressed"); }
	}
	void CreditsScene::render()
	{
		background.render();
		m_graphicsLayer.draw();
		guiLayer.render();
	}

	HowToGolfScene::HowToGolfScene()
		:m_graphicsLayer(*AppData::getSus().GetShader("DefaultShader.glsl"), m_camera) {

		//===Tutorial Sheet:
		tutorialSheet.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		tutorialSheet.getComponent<GUIComponent>()->setPosition(PositionType::CENTER, 0.0f, 0.0f, ModeType::RELATIVE);
		tutorialSheet.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		tutorialSheet.getComponent<VisualComponent>()->setTexture("HowToGolf");
		tutorialSheet.getTransform()->setScale(1.08f*1.4f, 0.72f * 1.4f);

		//===main Menu button:
		mainMenuButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		mainMenuButton.getComponent<GUIComponent>()->setPosition(PositionType::BOTTOMLEFT, 0.03f, 0.03f, ModeType::RELATIVE);
		mainMenuButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		mainMenuButton.getComponent<VisualComponent>()->setTexture("return_not_pressed");
		mainMenuButton.getTransform()->setScale(0.12f, 0.12f);
		mainMenuButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));
	}
	void HowToGolfScene::update([[maybe_unused]] float deltaT) {
		auto ptr = mainMenuButton.getComponent<ButtonComponent>();
		ptr->update();
		if (ptr->isClicked()) {
			auto next = std::shared_ptr<Scene>(new MainMenu());
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(shared_from_this(), next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
		}
		if (ptr->isHovered()) {
			mainMenuButton.getComponent<VisualComponent>()->setTexture("return_pressed");
		}
		else { mainMenuButton.getComponent<VisualComponent>()->setTexture("return_not_pressed"); }
	}
	void HowToGolfScene::render()
	{
		background.render();
		m_graphicsLayer.draw();
		guiLayer.render();
	}

	////////////////////////////
	/// BlackScene
	////////////////////////////

	BlackScene::BlackScene()
		:m_graphicsLayer(*AppData::getSus().GetShader("DefaultShader.glsl"), m_camera) {
	}
	void BlackScene::update([[maybe_unused]] float deltaT) {
		m_timer -= deltaT * 10.f;
		if(m_timer < 0) {
			auto next = std::shared_ptr<Scene>(new MainMenu());
			auto transition = std::shared_ptr<Scene>(new TransitionSceneFade(shared_from_this(), next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
			m_timer = 999.f;
		}
	}
	void BlackScene::render() {
		m_graphicsLayer.draw();
	}

	EndScreen::EndScreen()
		:m_graphicsLayer(*AppData::getSus().GetShader("DefaultShader.glsl"), m_camera)
	{

		AppData::getInput().attachCamera(&m_camera, 1.0f);

		menuButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		menuButton.getComponent<GUIComponent>()->setPosition(PositionType::CENTER, 0.f, -0.3f, ModeType::RELATIVE);
		menuButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		menuButton.getComponent<VisualComponent>()->setTexture("menu_not_pressed");
		menuButton.getTransform()->setScale(0.2f, 0.2f);
		menuButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		ThankYou.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		ThankYou.getComponent<GUIComponent>()->setPosition(PositionType::CENTER, 0.0f, 0.1f, ModeType::RELATIVE);
		ThankYou.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		ThankYou.getComponent<VisualComponent>()->setTexture("thank_you");
		ThankYou.getTransform()->setScale(1.2f, 0.14f);
		
	}

	void EndScreen::update([[maybe_unused]] float deltaT)
	{
		//quit
		auto ptr = menuButton.getComponent<ButtonComponent>();
		ptr->update();
		if (ptr->isClicked()) {
			auto next = std::shared_ptr<Scene>(new MainMenu());
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(shared_from_this(), next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
		}
		if (ptr->isHovered()) {
			menuButton.getComponent<VisualComponent>()->setTexture("menu_pressed");
		}
		else { menuButton.getComponent<VisualComponent>()->setTexture("menu_not_pressed"); }

	}

	void EndScreen::render()
	{
		background.render();
		m_graphicsLayer.draw();
		guiLayer.render();
	}
}


//NOLINTEND(readability-function-cognitive-complexity)
