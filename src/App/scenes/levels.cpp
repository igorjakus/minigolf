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
		AppData::getInput().attachCamera(&m_camera, 10.0f);


		pauseButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		pauseButton.getComponent<GUIComponent>()->setPosition(PositionType::TOPRIGHT, -0.01f, -0.01f, ModeType::RELATIVE);
		pauseButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		pauseButton.getComponent<VisualComponent>()->setTexture("popcat");
		pauseButton.getTransform()->setScale(0.1f, 0.1f);
		pauseButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		frame1.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame1.getComponent<VisualComponent>()->setColor(255, 0, 0, 255);
		frame1.getTransform()->setPos(0.0f, 3.0f);
		frame1.getTransform()->setScale(0.2f, 6.19f);

		frame2.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame2.getComponent<VisualComponent>()->setColor(255, 0, 0, 255);
		frame2.getTransform()->setPos(4.0f, 6.0f);
		frame2.getTransform()->setScale(8.15f, 0.2f);

		frame3.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame3.getComponent<VisualComponent>()->setColor(255, 0, 0, 255);
		frame3.getTransform()->setPos(8.1f, 3.0f);
		frame3.getTransform()->setScale(0.2f, 6.19f);

		frame4.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame4.getComponent<VisualComponent>()->setColor(255, 0, 0, 255);
		frame4.getTransform()->setPos(4.0f, 0.0f);
		frame4.getTransform()->setScale(8.15f, 0.2f);

		wallA.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		wallA.getComponent<VisualComponent>()->setTexture("popcat");
		wallA.getTransform()->setPos(3.0f, 2.0f);
		wallA.getTransform()->setScale(6.0f, 0.2f);

		wallB.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		wallB.getComponent<VisualComponent>()->setColor(255, 0, 255, 255);
		wallB.getTransform()->setPos(5.0f, 4.0f);
		wallB.getTransform()->setScale(6.0f, 0.2f);

	}

	void LevelOneScene::update([[maybe_unused]] float deltaT)
	{

		if (AppData::getInput().isKeyPressed("UP")) {
			m_camera.setPosition(m_camera.getPosition().x, m_camera.getPosition().y + deltaT * 5);
		}

		if (AppData::getInput().isKeyPressed("LEFT")) {
			m_camera.setPosition(m_camera.getPosition().x - deltaT * 5, m_camera.getPosition().y);
		}

		if (AppData::getInput().isKeyPressed("RIGHT")) {
			m_camera.setPosition(m_camera.getPosition().x + deltaT * 5, m_camera.getPosition().y);
		}
		if (AppData::getInput().isKeyPressed("DOWN")) {
			m_camera.setPosition(m_camera.getPosition().x, m_camera.getPosition().y - deltaT * 5);
		}
		auto ptr = pauseButton.getComponent<ButtonComponent>();
		ptr->update();
		if (ptr->isClicked()) {
			AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new LevelSelectionScene()));
			AppData::getSceneManager().nextScene();
		}
		if (ptr->isHovered()) {
			pauseButton.getComponent<VisualComponent>()->setTexture("sponge");
		}
		else { pauseButton.getComponent<VisualComponent>()->setTexture("popcat"); }


	}

	void LevelOneScene::render() {
		m_graphicsLayer.draw();
		guiLayer.render();
	}



	// ===============================
	// LevelTwoScene
	// ===============================


	LevelTwoScene::LevelTwoScene()
		: m_camera(0.f, 0.f, 1.f, 1.f, 1.f),
		m_graphicsLayer(*AppData::getSus().GetShader("DefaultShader.glsl"), m_camera) {
		AppData::getInput().attachCamera(&m_camera, 10.0f);


		pauseButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		pauseButton.getComponent<GUIComponent>()->setPosition(PositionType::TOPRIGHT, -0.01f, -0.01f, ModeType::RELATIVE);
		pauseButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		pauseButton.getComponent<VisualComponent>()->setTexture("popcat");
		pauseButton.getTransform()->setScale(0.1f, 0.1f);
		pauseButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		frame1.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame1.getComponent<VisualComponent>()->setColor(255, 0, 0, 255);
		frame1.getTransform()->setPos(0.0f, 3.0f);
		frame1.getTransform()->setScale(0.2f, 6.19f);

		frame2.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame2.getComponent<VisualComponent>()->setColor(255, 0, 0, 255);
		frame2.getTransform()->setPos(4.0f, 6.0f);
		frame2.getTransform()->setScale(8.15f, 0.2f);

		frame3.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame3.getComponent<VisualComponent>()->setColor(255, 0, 0, 255);
		frame3.getTransform()->setPos(8.1f, 3.0f);
		frame3.getTransform()->setScale(0.2f, 6.19f);

		frame4.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame4.getComponent<VisualComponent>()->setColor(255, 0, 0, 255);
		frame4.getTransform()->setPos(4.0f, 0.0f);
		frame4.getTransform()->setScale(8.15f, 0.2f);

		wallA.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		wallA.getComponent<VisualComponent>()->setTexture("popcat");
		wallA.getTransform()->setPos(2.5f, 3.0f);
		wallA.getTransform()->setScale( 0.2f, 2.0f);

		wallB.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		wallB.getComponent<VisualComponent>()->setColor(255, 0, 255, 255);
		wallB.getTransform()->setPos(5.5f, 3.0f);
		wallB.getTransform()->setScale(0.2f, 2.0f);


	}

	void LevelTwoScene::update([[maybe_unused]] float deltaT)
	{
		
		if (AppData::getInput().isKeyPressed("UP")) {
			m_camera.setPosition(m_camera.getPosition().x, m_camera.getPosition().y + deltaT * 5);
		}

		if (AppData::getInput().isKeyPressed("LEFT")) {
			m_camera.setPosition(m_camera.getPosition().x - deltaT * 5, m_camera.getPosition().y);
		}

		if (AppData::getInput().isKeyPressed("RIGHT")) {
			m_camera.setPosition(m_camera.getPosition().x + deltaT * 5, m_camera.getPosition().y);
		}
		if (AppData::getInput().isKeyPressed("DOWN")) {
			m_camera.setPosition(m_camera.getPosition().x, m_camera.getPosition().y - deltaT * 5);
		}
		auto ptr = pauseButton.getComponent<ButtonComponent>();
		ptr->update();
		if (ptr->isClicked()) {
			AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new LevelSelectionScene()));
			AppData::getSceneManager().nextScene();
		}
		if (ptr->isHovered()) {
			pauseButton.getComponent<VisualComponent>()->setTexture("sponge");
		}
		else { pauseButton.getComponent<VisualComponent>()->setTexture("popcat"); }


		static bool moveUp = true; 
		float wallSpeed = 1.0f; 

		if (moveUp) {
			wallA.getTransform()->setPos(wallA.getTransform()->getPos().first, wallA.getTransform()->getPos().second + deltaT * wallSpeed);
		}
		else {
			wallA.getTransform()->setPos(wallA.getTransform()->getPos().first, wallA.getTransform()->getPos().second - deltaT * wallSpeed);
		}

		if (moveUp) {
			wallB.getTransform()->setPos(wallB.getTransform()->getPos().first, wallB.getTransform()->getPos().second - deltaT * wallSpeed);
		}
		else {
			wallB.getTransform()->setPos(wallB.getTransform()->getPos().first, wallB.getTransform()->getPos().second + deltaT * wallSpeed);
			
		}

		
		float upperLimit = 4.8f;  
		float lowerLimit = 1.2f;  

		if (wallA.getTransform()->getPos().second >= upperLimit) {
			moveUp = false;
		}
		else if (wallA.getTransform()->getPos().second <= lowerLimit) {
			moveUp = true;
		}

	}

	void LevelTwoScene::render() {
		m_graphicsLayer.draw();
		guiLayer.render();
	}


	// ===============================
	// LevelThreeScene
	// ===============================

	LevelThreeScene::LevelThreeScene()
		: m_camera(0.f, 0.f, 1.f, 1.f, 1.f),
		m_graphicsLayer(*AppData::getSus().GetShader("DefaultShader.glsl"), m_camera) {
		AppData::getInput().attachCamera(&m_camera, 10.0f);


		pauseButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		pauseButton.getComponent<GUIComponent>()->setPosition(PositionType::TOPRIGHT, -0.01f, -0.01f, ModeType::RELATIVE);
		pauseButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		pauseButton.getComponent<VisualComponent>()->setTexture("popcat");
		pauseButton.getTransform()->setScale(0.1f, 0.1f);
		pauseButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		frame1.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame1.getComponent<VisualComponent>()->setColor(255, 0, 0, 255);
		frame1.getTransform()->setPos(0.0f, 3.0f);
		frame1.getTransform()->setScale(0.2f, 8.2f);

		frame2.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame2.getComponent<VisualComponent>()->setColor(255, 0, 0, 255);
		frame2.getTransform()->setPos(4.0f, 7.0f);
		frame2.getTransform()->setScale(8.0f, 0.2f);

		frame3.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame3.getComponent<VisualComponent>()->setColor(255, 0, 0, 255);
		frame3.getTransform()->setPos(8.1f, 3.0f);
		frame3.getTransform()->setScale(0.2f, 8.2f);

		frame4.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame4.getComponent<VisualComponent>()->setColor(255, 0, 0, 255);
		frame4.getTransform()->setPos(4.0f, -1.0f);
		frame4.getTransform()->setScale(8.0f, 0.2f);

		wallA.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		wallA.getComponent<VisualComponent>()->setTexture("popcat");
		wallA.getTransform()->setPos(4.0f, 3.0f);
		wallA.getTransform()->setScale(6.0f, 0.2f);

		wallB.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		wallB.getComponent<VisualComponent>()->setColor(255, 0, 255, 255);
		wallB.getTransform()->setPos(4.0f, 3.0f);
		wallB.getTransform()->setScale(0.2f, 6.0f);

	}

	void LevelThreeScene::update([[maybe_unused]] float deltaT)
	{

		if (AppData::getInput().isKeyPressed("UP")) {
			m_camera.setPosition(m_camera.getPosition().x, m_camera.getPosition().y + deltaT * 5);
		}

		if (AppData::getInput().isKeyPressed("LEFT")) {
			m_camera.setPosition(m_camera.getPosition().x - deltaT * 5, m_camera.getPosition().y);
		}

		if (AppData::getInput().isKeyPressed("RIGHT")) {
			m_camera.setPosition(m_camera.getPosition().x + deltaT * 5, m_camera.getPosition().y);
		}
		if (AppData::getInput().isKeyPressed("DOWN")) {
			m_camera.setPosition(m_camera.getPosition().x, m_camera.getPosition().y - deltaT * 5);
		}
		auto ptr = pauseButton.getComponent<ButtonComponent>();
		ptr->update();
		if (ptr->isClicked()) {
			AppData::getSceneManager().pushScene(std::shared_ptr<Scene>(new LevelSelectionScene()));
			AppData::getSceneManager().nextScene();
		}
		if (ptr->isHovered()) {
			pauseButton.getComponent<VisualComponent>()->setTexture("sponge");
		}
		else { pauseButton.getComponent<VisualComponent>()->setTexture("popcat"); }

		float rotateSpeed = 45.0f;  // Dostosuj prêdkoœæ obrotu wallA
		wallA.getTransform()->rot += deltaT * rotateSpeed;
		wallB.getTransform()->rot += deltaT * rotateSpeed;



	}

	void LevelThreeScene::render() {
		m_graphicsLayer.draw();
		guiLayer.render();
	}

}