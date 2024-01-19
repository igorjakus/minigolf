#include "pch.h"
#include "levels.h"
#include "misc.h"
#include "transition.h"
#include "../Graphics.h"
#include "../Core/AppData.h"


namespace golf {


	using PositionType = GUIComponent::positionType;
	using ModeType = GUIComponent::modeType;

	// ===============================
	// LevelOneScene
	// ===============================

	LevelOneScene::LevelOneScene()
		:m_graphicsLayer(*AppData::getSus().GetShader("DefaultShader.glsl"), m_camera)
	{
		AppData::getInput().attachCamera(&m_camera, 10.0f);

		pauseButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		pauseButton.getComponent<GUIComponent>()->setPosition(PositionType::TOPRIGHT, -0.01f, -0.01f, ModeType::RELATIVE);
		pauseButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		pauseButton.getComponent<VisualComponent>()->setTexture("popcat");
		pauseButton.getTransform()->setScale(0.1f, 0.1f);
		pauseButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		///////////////////////////
		// Tu ci trawke dodalem
		///////////////////////////
		grass.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		grass.getComponent<VisualComponent>()->setTexture("Grass");
		grass.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		grass.getTransform()->setScale(8.0f, 6.0f);
		grass.getTransform()->setPos(4, 3);

		frame1.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		frame1.getComponent<VisualComponent>()->setTexture("Wood");
		frame1.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		frame1.getTransform()->setPos(0.0f, 3.0f);
		frame1.getTransform()->setScale(0.2f, 6.19f);

		frame2.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		frame2.getComponent<VisualComponent>()->setTexture("Wood");
		frame2.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		frame2.getTransform()->setPos(4.0f, 6.0f);
		frame2.getTransform()->setScale(8.15f, 0.2f);

		frame3.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		frame3.getComponent<VisualComponent>()->setTexture("Wood");
		frame3.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		frame3.getTransform()->setPos(8.1f, 3.0f);
		frame3.getTransform()->setScale(0.2f, 6.19f);

		frame4.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		frame4.getComponent<VisualComponent>()->setTexture("Wood");
		frame4.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		frame4.getTransform()->setPos(4.0f, 0.0f);
		frame4.getTransform()->setScale(8.15f, 0.2f);

		wallA.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		wallA.getComponent<VisualComponent>()->setTexture("Wood");
		wallA.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		wallA.getTransform()->setPos(3.0f, 2.0f);
		wallA.getTransform()->setScale(6.0f, 0.2f);

		wallB.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		wallB.getComponent<VisualComponent>()->setTexture("Wood");
		wallB.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		wallB.getTransform()->setPos(5.0f, 4.0f);
		wallB.getTransform()->setScale(6.0f, 0.2f);

	}

	void LevelOneScene::update(float deltaT)
	{
		
		const float cameraSpeed = 5;
		if (AppData::getInput().isKeyPressed("UP")) {
			m_camera.setPosition(m_camera.getPosition().x, m_camera.getPosition().y + deltaT * cameraSpeed);
		}

		if (AppData::getInput().isKeyPressed("LEFT")) {
			m_camera.setPosition(m_camera.getPosition().x - deltaT * cameraSpeed, m_camera.getPosition().y );
		}

		if (AppData::getInput().isKeyPressed("RIGHT")) {
			m_camera.setPosition(m_camera.getPosition().x + deltaT * cameraSpeed, m_camera.getPosition().y );
		}
		if (AppData::getInput().isKeyPressed("DOWN")) {
			m_camera.setPosition(m_camera.getPosition().x, m_camera.getPosition().y - deltaT * cameraSpeed);
		}

		auto ptr = pauseButton.getComponent<ButtonComponent>();
		ptr->update();
		if (ptr->isClicked()) {
			auto next = std::shared_ptr<Scene>(new LevelSelectionScene());
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(shared_from_this(), next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
		}
		if (ptr->isHovered()) {
			pauseButton.getComponent<VisualComponent>()->setTexture("sponge");
		}
		else { pauseButton.getComponent<VisualComponent>()->setTexture("popcat"); }

	
	}

	void LevelOneScene::render()
	{ 
		m_graphicsLayer.draw(); 
		guiLayer.render();
	}



	// ===============================
	// LevelTwoScene
	// ===============================


	LevelTwoScene::LevelTwoScene()
		:m_graphicsLayer(*AppData::getSus().GetShader("DefaultShader.glsl"), m_camera)
	{
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

	void LevelTwoScene::update(float deltaT)
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
		:m_graphicsLayer(*AppData::getSus().GetShader("DefaultShader.glsl"), m_camera) {
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

	void LevelThreeScene::update(float deltaT)
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


	// ===============================
	// LevelFourScene
	// ===============================

	LevelFourScene::LevelFourScene()
		:m_graphicsLayer(*AppData::getSus().GetShader("DefaultShader.glsl"), m_camera) {
		AppData::getInput().attachCamera(&m_camera, 10.0f);


		pauseButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		pauseButton.getComponent<GUIComponent>()->setPosition(PositionType::TOPRIGHT, -0.01f, -0.01f, ModeType::RELATIVE);
		pauseButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		pauseButton.getComponent<VisualComponent>()->setTexture("popcat");
		pauseButton.getTransform()->setScale(0.1f, 0.1f);
		pauseButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));
		frame1.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame1.getComponent<VisualComponent>()->setColor(255, 0, 0, 255);
		frame1.getTransform()->setPos(0.0f, -2.9f);
		frame1.getTransform()->setScale(0.2f, 10.0f);

		frame2.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame2.getComponent<VisualComponent>()->setColor(255, 0, 0, 255);
		frame2.getTransform()->setPos(2.5f, 2.0f);
		frame2.getTransform()->setScale(5.0f, 0.2f);

		frame3.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame3.getComponent<VisualComponent>()->setColor(255, 0, 0, 255);
		frame3.getTransform()->setPos(6.35f, 0.6f);
		frame3.getTransform()->setScale(0.2f, 4.0f);
		frame3.getTransform()->rot = 45.0f;

		frame4.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame4.getComponent<VisualComponent>()->setColor(255, 0, 0, 255);
		frame4.getTransform()->setPos(1.5f, 0.0f);
		frame4.getTransform()->setScale(3.0f, 0.2f);

		frame5.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame5.getComponent<VisualComponent>()->setColor(255, 0, 0, 255);
		frame5.getTransform()->setPos(7.75f, -4.35f);
		frame5.getTransform()->setScale( 0.2f, 7.2f);

		frame6.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame6.getComponent<VisualComponent>()->setColor(255, 0, 0, 255);
		frame6.getTransform()->setPos(3.875f, -7.9f);
		frame6.getTransform()->setScale(7.95f,0.2f);

		wall1.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		wall1.getComponent<VisualComponent>()->setTexture("popcat");
		wall1.getTransform()->setPos(2.5f, -2.0f);
		wall1.getTransform()->setScale(2.5f, 0.2f);

		wall2.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		wall2.getComponent<VisualComponent>()->setTexture("popcat");
		wall2.getTransform()->setPos(5.5f, -3.5f);
		wall2.getTransform()->setScale(2.5f, 0.2f);
		wall2.getTransform()->rot = 20.0f;


		wall3.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		wall3.getComponent<VisualComponent>()->setTexture("popcat");
		wall3.getTransform()->setPos(2.5f, -5.5f);
		wall3.getTransform()->setScale(2.5f, 0.2f);
		wall3.getTransform()->rot = 100.0f;

		

		

	}

	void LevelFourScene::update(float deltaT)
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

		float rotateSpeed1 = 80.0f; 
		
		wall1.getTransform()->rot -= deltaT * rotateSpeed1;
		wall2.getTransform()->rot += deltaT * rotateSpeed1;
		wall3.getTransform()->rot -= deltaT * rotateSpeed1;
	}

	void LevelFourScene::render() {
		m_graphicsLayer.draw();
		guiLayer.render();
	}

	// ===============================
	// LevelFiveScene
	// ===============================

	LevelFiveScene::LevelFiveScene()
		: m_camera(0.f, 0.f, 1.f, 1.f, 1.f),
		m_graphicsLayer(*AppData::getSus().GetShader("DefaultShader.glsl"), m_camera) {
		AppData::getInput().attachCamera(&m_camera, 20.0f);
		
		pauseButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		pauseButton.getComponent<GUIComponent>()->setPosition(PositionType::TOPRIGHT, -0.01f, -0.01f, ModeType::RELATIVE);
		pauseButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		pauseButton.getComponent<VisualComponent>()->setTexture("popcat");
		pauseButton.getTransform()->setScale(0.1f, 0.1f);
		pauseButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		frame1.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame1.getComponent<VisualComponent>()->setColor(255, 0, 0, 255);
		frame1.getTransform()->setPos(0.0f, 6.0f);
		frame1.getTransform()->setScale(0.2f, 12.19f);

		frame2.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame2.getComponent<VisualComponent>()->setColor(255, 0, 0, 255);
		frame2.getTransform()->setPos(8.0f, 12.0f);
		frame2.getTransform()->setScale(16.15f, 0.2f);

		frame3.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame3.getComponent<VisualComponent>()->setColor(255, 0, 0, 255);
		frame3.getTransform()->setPos(16.1f, 6.0f);
		frame3.getTransform()->setScale(0.2f, 12.19f);

		frame4.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame4.getComponent<VisualComponent>()->setColor(255, 0, 0, 255);
		frame4.getTransform()->setPos(8.0f, 0.0f);
		frame4.getTransform()->setScale(16.15f, 0.2f);


		wallB.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		wallB.getComponent<VisualComponent>()->setColor(255, 0, 255, 255);
		wallB.getTransform()->setPos(8.0f, 6.0f);
		wallB.getTransform()->setScale(9.0f, 0.8f);

		w1.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		w1.getComponent<VisualComponent>()->setColor(255, 0, 255, 255);
		w1.getTransform()->setPos(5.0f, 9.2f);
		w1.getTransform()->setScale(4.0f, 0.2f);

		w2.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		w2.getComponent<VisualComponent>()->setColor(255, 0, 255, 255);
		w2.getTransform()->setPos(5.0f, 9.2f);
		w2.getTransform()->setScale(0.2f, 4.0f);

		w3.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		w3.getComponent<VisualComponent>()->setColor(255, 0, 255, 255);
		w3.getTransform()->setPos(11.0f, 9.2f);
		w3.getTransform()->setScale(4.0f, 0.2f);

		w4.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		w4.getComponent<VisualComponent>()->setColor(255, 0, 255, 255);
		w4.getTransform()->setPos(11.0f, 9.2f);
		w4.getTransform()->setScale( 0.2f, 4.0f);

		q1.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		q1.getComponent<VisualComponent>()->setColor(255, 0, 255, 255);
		q1.getTransform()->setPos(5.0f, 2.2f);
		q1.getTransform()->setScale(1.0f, 2.0f);


		q2.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		q2.getComponent<VisualComponent>()->setColor(255, 0, 255, 255);
		q2.getTransform()->setPos(8.0f, 2.7f);
		q2.getTransform()->setScale(1.0f, 2.0f);


		q3.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		q3.getComponent<VisualComponent>()->setColor(255, 0, 255, 255);
		q3.getTransform()->setPos(11.0f, 3.3f);
		q3.getTransform()->setScale(1.0f, 2.0f);

	}

	void LevelFiveScene::update([[maybe_unused]] float deltaT)
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

		float rotateSpeed1 = 80.0f;

		w1.getTransform()->rot += deltaT * rotateSpeed1;
		w2.getTransform()->rot += deltaT * rotateSpeed1;
		w3.getTransform()->rot -= deltaT * rotateSpeed1;
		w4.getTransform()->rot -= deltaT * rotateSpeed1;
		


		static bool moveUp1 = true;
		static bool moveUp2 = false;
		static bool moveUp3 = true;
		float wallSpeed1 = 1.0f;
		float wallSpeed2 = 1.5f;

		if (moveUp1) {
			q1.getTransform()->setPos(q1.getTransform()->getPos().first, q1.getTransform()->getPos().second + deltaT * wallSpeed1);
		}
		else {
			q1.getTransform()->setPos(q1.getTransform()->getPos().first, q1.getTransform()->getPos().second - deltaT * wallSpeed1);
		}

		if (moveUp2) {
			q2.getTransform()->setPos(q2.getTransform()->getPos().first, q2.getTransform()->getPos().second + deltaT * wallSpeed1);
		}
		else {
			q2.getTransform()->setPos(q2.getTransform()->getPos().first, q2.getTransform()->getPos().second - deltaT * wallSpeed1);
		}

		if (moveUp3) {
			q3.getTransform()->setPos(q3.getTransform()->getPos().first, q3.getTransform()->getPos().second + deltaT * wallSpeed2);
		}
		else {
			q3.getTransform()->setPos(q3.getTransform()->getPos().first, q3.getTransform()->getPos().second - deltaT * wallSpeed2);
		}

		float upperLimit = 4.6f;
		float lowerLimit = 1.1f;

		if (q1.getTransform()->getPos().second >= upperLimit) {
			moveUp1 = false;
		}
		else if (q1.getTransform()->getPos().second <= lowerLimit) {
			moveUp1 = true;
		}

		if (q2.getTransform()->getPos().second >= upperLimit) {
			moveUp2 = false;
		}
		else if (q2.getTransform()->getPos().second <= lowerLimit) {
			moveUp2 = true;
		}

		if (q3.getTransform()->getPos().second >= upperLimit) {
			moveUp3 = false;
		}
		else if (q3.getTransform()->getPos().second <= lowerLimit) {
			moveUp3 = true;
		}

	}

	void LevelFiveScene::render() {
		m_graphicsLayer.draw();
		guiLayer.render();
	}

}


