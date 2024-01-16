#include "pch.h"
#include "../Graphics.h"
#include "levels.h"
#include "../Core/AppData.h"
#include "misc.h"

namespace golf {


	using PositionType = GUIComponent::positionType;
	using ModeType = GUIComponent::modeType;

	// ===============================
	// LevelOneScene
	// ===============================

	LevelOneScene::LevelOneScene()
		: m_camera(0.f, 0.f, 1.f, 1.f, 1.f),
		m_graphicsLayer(*AppData::getSus().GetShader("DefaultShader.glsl"), m_camera) {
		const float tempX = static_cast<float>(AppData::getWindow().getWindowSize().x);
		const float tempY = static_cast<float>(AppData::getWindow().getWindowSize().y);
		m_camera.setSize(tempX / tempY, 1.0f);

		wallA.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		wallA.getComponent<VisualComponent>()->setColor(255, 0, 0, 255);
		wallA.getTransform()->setPos(0.3f, 0.0f);
		wallA.getTransform()->setScale(0.05f, 0.2f);

		wallB.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		wallB.getComponent<VisualComponent>()->setColor(255, 0, 255, 255);
		wallB.getTransform()->setPos(0.1f, 0.0f);
		wallB.getTransform()->setScale(0.05f, 0.2f);

	}

	void LevelOneScene::update([[maybe_unused]] float deltaT)
	{
		if (isFirstUpdate) {
			DTL_INF("level one scene -- click q to quit, r to play again, w to win");
			isFirstUpdate = false;
		}
		//quit
		if (AppData::getInput().isKeyClicked("Q")) {
			AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new LevelSelectionScene()));
			AppData::getSceneManager().nextScene();
		}
		//retry
		if (AppData::getInput().isKeyClicked("R")) {
			AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new LevelOneScene()));
			AppData::getSceneManager().nextScene();
		}
		//won
		if (AppData::getInput().isKeyClicked("W")) {
			AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new ResultsScene(10, 1)));
			AppData::getSceneManager().nextScene();
		}

	}

	void LevelOneScene::render() { m_graphicsLayer.draw(); }



	// ===============================
	// LevelTwoScene
	// ===============================


	LevelTwoScene::LevelTwoScene()
		:m_camera(0.F, 0.F, 1.F, 1.F, 1.F),
		m_graphicsLayer(*AppData::getSus().GetShader("DefaultShader.glsl"), m_camera)
	{
		const float tempX = static_cast<float>(AppData::getWindow().getWindowSize().x);
		const float tempY = static_cast<float>(AppData::getWindow().getWindowSize().y);
		m_camera.setSize(tempX / tempY, 1.0f);
	}

	void LevelTwoScene::update([[maybe_unused]] float deltaT)
	{
		if (isFirstUpdate) {
			DTL_INF("level two scene -- click q to quit, r to play again, w to win");
			isFirstUpdate = false;
		}
		//quit
		if (AppData::getInput().isKeyClicked("Q")) {
			AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new LevelSelectionScene()));
			AppData::getSceneManager().nextScene();
		}
		//play again
		if (AppData::getInput().isKeyClicked("R")) {
			AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new LevelTwoScene()));
			AppData::getSceneManager().nextScene();
		}

		//won
		if (AppData::getInput().isKeyClicked("W")) {
			AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new ResultsScene(100, 2)));
			AppData::getSceneManager().nextScene();
		}
	}

	void LevelTwoScene::render()
	{
		m_graphicsLayer.draw();
	}
}