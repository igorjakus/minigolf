#include "App/Slingshot.h"
#include "pch.h"
#include "levels.h"
#include "misc.h"
#include "transition.h"
#include "../Graphics.h"
#include "../Core/AppData.h"

#include "Util/GML/LinearAlgebra/Vec3f.h"
#include "Util/GML/LinearAlgebra/Vec2f.h"
#include "Util/GML/Constants.h"
#include "Util/Util.hpp"
#include <memory>

//NOLINTBEGIN(readability-function-cognitive-complexity)

namespace golf {

	using PositionType = GUIComponent::positionType;
	using ModeType = GUIComponent::modeType;

	// ===============================
	// LevelOneScene
	// ===============================

	LevelOneScene::LevelOneScene()
		:m_graphicsLayer(*AppData::getSus().GetShader("DefaultShader.glsl"), m_camera),
		cameraControls(m_camera, 0.f, 8.f, 6.f, 0.f)
	{
		AppData::getInput().attachCamera(&m_camera, 10.0f);
		m_camera.setPosition(1.f, 1.f);

		grass.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		grass.getComponent<VisualComponent>()->setTexture("Grass");
		grass.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		grass.getTransform()->setScale(8.0f, 6.0f);
		grass.getTransform()->setPos(4, 3);

		wallA.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		wallA.getComponent<VisualComponent>()->setTexture("Wood");
		wallA.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		wallA.getTransform()->setPos(3.0f, 2.0f);
		wallA.getTransform()->setScale(6.0f, 0.2f);
		wallA.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		wallA.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		wallB.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		wallB.getComponent<VisualComponent>()->setTexture("Wood");
		wallB.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		wallB.getTransform()->setPos(5.0f, 4.0f);
		wallB.getTransform()->setScale(6.0f, 0.2f);
		wallB.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		wallB.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		frame1.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		frame1.getComponent<VisualComponent>()->setColor(87, 34, 18, 255);
		frame1.getTransform()->setPos(0.0f, 3.0f);
		frame1.getTransform()->setScale(0.2f, 6.19f);
		frame1.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		frame1.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		frame2.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		frame2.getComponent<VisualComponent>()->setColor(87, 34, 18, 255);
		frame2.getTransform()->setPos(4.0f, 6.0f);
		frame2.getTransform()->setScale(8.15f, 0.2f);
		frame2.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		frame2.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		frame3.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		frame3.getComponent<VisualComponent>()->setColor(87, 34, 18, 255);
		frame3.getTransform()->setPos(8.1f, 3.0f);
		frame3.getTransform()->setScale(0.2f, 6.19f);
		frame3.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		frame3.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		frame4.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		frame4.getComponent<VisualComponent>()->setColor(87, 34, 18, 255);
		frame4.getTransform()->setPos(4.0f, 0.0f);
		frame4.getTransform()->setScale(8.15f, 0.2f);
		frame4.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		frame4.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));




		hole.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		hole.getComponent<VisualComponent>()->setTexture("hole");
		hole.getTransform()->setPos(7.0f, 5.0f);
		hole.getTransform()->setScale(0.5f);

		ball.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		ball.getComponent<VisualComponent>()->setTexture("Ball");
		ball.getTransform()->setPos(1.0f, 1.0f);
		ball.getTransform()->setScale(0.2f);
		ball.addComponent<DynamicPhysicsComponent>(physics.addDynamicElement(0.1f, 0.001f));
		ball.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Kula, 0.1f));
		ball.addComponent<SlingshotComponent>(std::make_shared<SlingshotComponent>(m_camera, m_graphicsLayer));

		/////////////////
		// GUI
		/////////////////

		pauseButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		pauseButton.getComponent<GUIComponent>()->setPosition(PositionType::TOPRIGHT, -0.05f, -0.05f, ModeType::RELATIVE);
		pauseButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		pauseButton.getTransform()->setScale(0.1f, 0.1f);
		pauseButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		replayButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		replayButton.getComponent<GUIComponent>()->setPosition(PositionType::TOPRIGHT, -0.05f, -0.16f, ModeType::RELATIVE);
		replayButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		replayButton.getTransform()->setScale(0.1f, 0.1f);
		replayButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		camLockButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		camLockButton.getComponent<GUIComponent>()->setPosition(PositionType::TOPRIGHT, -0.05f, -0.27f, ModeType::RELATIVE);
		camLockButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		camLockButton.getTransform()->setScale(0.1f, 0.1f);
		camLockButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		firstDigit.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		firstDigit.getComponent<GUIComponent>()->setPosition(PositionType::TOPLEFT, 0.105f, -0.05f, ModeType::RELATIVE);
		firstDigit.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		firstDigit.getTransform()->setScale(0.1f, 0.1f);
		firstDigit.getComponent<VisualComponent>()->setTexture("0");

		secondDigit.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		secondDigit.getComponent<GUIComponent>()->setPosition(PositionType::TOPLEFT, 0.05f, -0.05f, ModeType::RELATIVE);
		secondDigit.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		secondDigit.getTransform()->setScale(0.1f, 0.1f);
		secondDigit.getComponent<VisualComponent>()->setTexture("0");

		starDisplay.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		starDisplay.getComponent<GUIComponent>()->setPosition(PositionType::TOPLEFT, 0.045f, -0.11f, ModeType::RELATIVE);
		starDisplay.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		starDisplay.getTransform()->setScale(0.17f, 0.0633f);
	}

	void LevelOneScene::update(float deltaT)
	{
		// camera
		if (!camLocked) {
			if(ball.getComponent<DynamicPhysicsComponent>()->isMoving()) {
				cameraControls.follow(ball.getTransform()->x, ball.getTransform()->y);
			}
		} else {
			cameraControls.lock(4.f, 3.f, 0.65f);
		}
		cameraControls.update(deltaT);

		// ball
		ball.getComponent<SlingshotComponent>()->update(deltaT);
		if(ball.getComponent<SlingshotComponent>()->didShoot()) {
			score++;
		}

		// hole logic
		{
			float ballX = ball.getTransform()->x;
			float ballY = ball.getTransform()->y;
			float holeX = hole.getTransform()->x;
			float holeY = hole.getTransform()->y;
			GML::Vec3f dist = { holeX - ballX, holeY - ballY, 0 };
			uchar color = 255;
			if (dist.getLengthSquared() < hole.getTransform()->xScale * hole.getTransform()->xScale / 3) {
				ball.getComponent<DynamicPhysicsComponent>()->apply_force(5 * dist, {0, 0, 0});
				ball.getComponent<DynamicPhysicsComponent>()->apply_force(-1 * static_cast<GML::Vec3f>(ball.getComponent<DynamicPhysicsComponent>()->m_velocity), { 0, 0, 0 });
				float col = util::lerp(-50, 255, dist.getLength() / hole.getTransform()->xScale * 2);
				color = static_cast<uchar>(util::clamp(col, 0, 255));
				if (col < 0 && ball.getComponent<DynamicPhysicsComponent>()->m_velocity.getLength() < 0.03f) {
					won = true;
				}
			}
			ball.getComponent<VisualComponent>()->setColor(255, 255, 255, color);
		}

		physics.update(deltaT);

		// GUI

		auto ptr = pauseButton.getComponent<ButtonComponent>();
		if (!AppData::getInput().isMouseLocked()) { ptr->update(); }
		if (ptr->isClicked()) {
			auto next = std::shared_ptr<Scene>(new LevelSelectionScene());
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(shared_from_this(), next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
		}
		if (ptr->isHovered()) {
			pauseButton.getComponent<VisualComponent>()->setTexture("menu_pressed");
		}
		else { pauseButton.getComponent<VisualComponent>()->setTexture("menu_not_pressed"); }

		ptr = replayButton.getComponent<ButtonComponent>();
		if (!AppData::getInput().isMouseLocked()) { ptr->update(); }
		if (ptr->isClicked() || ball.getComponent<DynamicPhysicsComponent>()->exploded()) {
			AppData::getInput().setMousePosLock(false);
			auto next = std::shared_ptr<Scene>(new LevelOneScene());
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(shared_from_this(), next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
		}
		if (ptr->isHovered()) {
			replayButton.getComponent<VisualComponent>()->setTexture("replay_pressed");
		}
		else { replayButton.getComponent<VisualComponent>()->setTexture("replay_not_pressed"); }

		ptr = camLockButton.getComponent<ButtonComponent>();
		if (!AppData::getInput().isMouseLocked()) { ptr->update(); }
		if (ptr->isClicked()) {
			camLocked = !camLocked;
		}
		if (ptr->isHovered()) {
			if(camLocked){ camLockButton.getComponent<VisualComponent>()->setTexture("cam_locked_pressed"); }
			else { camLockButton.getComponent<VisualComponent>()->setTexture("cam_unlocked_pressed"); }
		}
		else {
			if (camLocked) { camLockButton.getComponent<VisualComponent>()->setTexture("cam_locked_not_pressed"); }
			else { camLockButton.getComponent<VisualComponent>()->setTexture("cam_unlocked_not_pressed"); }
		}

		
		firstDigit.getComponent<VisualComponent>()->setTexture(std::to_string(score % 10));
		secondDigit.getComponent<VisualComponent>()->setTexture(std::to_string((score%100)/10));

		if (score > 9) {
			stars = 0;
		}
		else if (score > 5) {
			stars = 1;
		}
		else if (score > 2) {
			stars = 2;
		}

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

		// Logika zakonczenia poziomu
		if (AppData::getInput().isKeyPressed("P") || won) {
			score--;
			if (score > 9) {
				stars = 0;
			}
			else if (score > 5) {
				stars = 1;
			}
			else if (score > 2) {
				stars = 2;
			}
			else {
				stars = 3;
			}
			auto next = std::shared_ptr<Scene>(new ResultsScene(score, stars, 1));
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(shared_from_this(), next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
			score++;
		}
	}

	void LevelOneScene::render()
	{ 
		background.render();
		m_graphicsLayer.draw(); 
		guiLayer.render();
	}

	// ===============================
	// LevelTwoScene
	// ===============================

	LevelTwoScene::LevelTwoScene()
		:m_graphicsLayer(*AppData::getSus().GetShader("DefaultShader.glsl"), m_camera),
	cameraControls(m_camera, 0.f, 8.f, 6.f, 0.f)
	{
		AppData::getInput().attachCamera(&m_camera, 10.0f);

		grass.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		grass.getComponent<VisualComponent>()->setTexture("Grass");
		grass.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		grass.getTransform()->setScale(8.0f, 6.0f);
		grass.getTransform()->setPos(4, 3);

		frame1.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame1.getComponent<VisualComponent>()->setColor(87, 34, 18, 255);
		frame1.getTransform()->setPos(0.0f, 3.0f);
		frame1.getTransform()->setScale(0.2f, 6.19f);
		frame1.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		frame1.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		frame2.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame2.getComponent<VisualComponent>()->setColor(87, 34, 18, 255);
		frame2.getTransform()->setPos(4.0f, 6.0f);
		frame2.getTransform()->setScale(8.15f, 0.2f);
		frame2.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		frame2.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		frame3.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame3.getComponent<VisualComponent>()->setColor(87, 34, 18, 255);
		frame3.getTransform()->setPos(8.1f, 3.0f);
		frame3.getTransform()->setScale(0.2f, 6.19f);
		frame3.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		frame3.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		frame4.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame4.getComponent<VisualComponent>()->setColor(87, 34, 18, 255);
		frame4.getTransform()->setPos(4.0f, 0.0f);
		frame4.getTransform()->setScale(8.15f, 0.2f);
		frame4.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		frame4.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		wallA.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		wallA.getComponent<VisualComponent>()->setTexture("Wood");
		wallA.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		wallA.getTransform()->setPos(2.5f, 3.0f);
		wallA.getTransform()->setScale( 0.2f, 2.0f);
		wallA.addComponent<KinematicPhysicsComponent>(physics.addKinematicElement());
		wallA.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		wallB.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		wallB.getComponent<VisualComponent>()->setTexture("Wood");
		wallB.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		wallB.getTransform()->setPos(5.5f, 3.0f);
		wallB.getTransform()->setScale(0.2f, 2.0f);
		wallB.addComponent<KinematicPhysicsComponent>(physics.addKinematicElement());
		wallB.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		hole.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		hole.getComponent<VisualComponent>()->setTexture("hole");
		hole.getTransform()->setPos(7.0f, 5.0f);
		hole.getTransform()->setScale(0.5f);

		ball.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		ball.getComponent<VisualComponent>()->setTexture("Ball");
		ball.getTransform()->setPos(1.0f, 1.0f);
		ball.getTransform()->setScale(0.2f);
		ball.addComponent<DynamicPhysicsComponent>(physics.addDynamicElement(0.1f, 0.001f));
		ball.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Kula, 0.1f));
		ball.addComponent<SlingshotComponent>(std::make_shared<SlingshotComponent>(m_camera, m_graphicsLayer));

		/////////////////
		// GUI
		/////////////////

		pauseButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		pauseButton.getComponent<GUIComponent>()->setPosition(PositionType::TOPRIGHT, -0.05f, -0.05f, ModeType::RELATIVE);
		pauseButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		pauseButton.getTransform()->setScale(0.1f, 0.1f);
		pauseButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		replayButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		replayButton.getComponent<GUIComponent>()->setPosition(PositionType::TOPRIGHT, -0.05f, -0.16f, ModeType::RELATIVE);
		replayButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		replayButton.getTransform()->setScale(0.1f, 0.1f);
		replayButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		camLockButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		camLockButton.getComponent<GUIComponent>()->setPosition(PositionType::TOPRIGHT, -0.05f, -0.27f, ModeType::RELATIVE);
		camLockButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		camLockButton.getTransform()->setScale(0.1f, 0.1f);
		camLockButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		firstDigit.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		firstDigit.getComponent<GUIComponent>()->setPosition(PositionType::TOPLEFT, 0.105f, -0.05f, ModeType::RELATIVE);
		firstDigit.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		firstDigit.getTransform()->setScale(0.1f, 0.1f);
		firstDigit.getComponent<VisualComponent>()->setTexture("0");

		secondDigit.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		secondDigit.getComponent<GUIComponent>()->setPosition(PositionType::TOPLEFT, 0.05f, -0.05f, ModeType::RELATIVE);
		secondDigit.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		secondDigit.getTransform()->setScale(0.1f, 0.1f);
		secondDigit.getComponent<VisualComponent>()->setTexture("0");

		starDisplay.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		starDisplay.getComponent<GUIComponent>()->setPosition(PositionType::TOPLEFT, 0.045f, -0.11f, ModeType::RELATIVE);
		starDisplay.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		starDisplay.getTransform()->setScale(0.17f, 0.0633f);
	}

	void LevelTwoScene::update(float deltaT)
	{
		// camera
		if (!camLocked) {
			if (ball.getComponent<DynamicPhysicsComponent>()->isMoving()) {
				cameraControls.follow(ball.getTransform()->x, ball.getTransform()->y);
			}
		}
		else {
			cameraControls.lock(4.f, 3.f, 0.65f);
		}
		cameraControls.update(deltaT);

		// ball
		ball.getComponent<SlingshotComponent>()->update(deltaT);
		if(ball.getComponent<SlingshotComponent>()->didShoot()) {
			score++;
		}

		// hole logic
		{
			float ballX = ball.getTransform()->x;
			float ballY = ball.getTransform()->y;
			float holeX = hole.getTransform()->x;
			float holeY = hole.getTransform()->y;
			GML::Vec3f dist = { holeX - ballX, holeY - ballY, 0 };
			uchar color = 255;
			if (dist.getLengthSquared() < hole.getTransform()->xScale * hole.getTransform()->xScale / 3) {
				ball.getComponent<DynamicPhysicsComponent>()->apply_force(5 * dist, { 0, 0, 0 });
				ball.getComponent<DynamicPhysicsComponent>()->apply_force(-1 * static_cast<GML::Vec3f>(ball.getComponent<DynamicPhysicsComponent>()->m_velocity), { 0, 0, 0 });
				float col = util::lerp(-50, 255, dist.getLength() / hole.getTransform()->xScale * 2);
				color = static_cast<uchar>(util::clamp(col, 0, 255));
				if (col < 0 && ball.getComponent<DynamicPhysicsComponent>()->m_velocity.getLength() < 0.03f) {
					won = true;
				}
			}
			ball.getComponent<VisualComponent>()->setColor(255, 255, 255, color);
		}

		physics.update(deltaT);
		
		
		// Moving obstacles

		const float wallSpeed = 1.f;
		static bool moveUp = true; 
		if (moveUp) {
			wallA.getComponent<KinematicPhysicsComponent>()->m_velocity = { 0, wallSpeed };
			wallB.getComponent<KinematicPhysicsComponent>()->m_velocity = { 0, -wallSpeed };
		} else {
			wallA.getComponent<KinematicPhysicsComponent>()->m_velocity = { 0, -wallSpeed };
			wallB.getComponent<KinematicPhysicsComponent>()->m_velocity = { 0, wallSpeed };
		}
		float upperLimit = 4.8f;  
		float lowerLimit = 1.2f;  
		if (wallA.getTransform()->getPos().second >= upperLimit) {
			moveUp = false;
		} else if (wallA.getTransform()->getPos().second <= lowerLimit) {
			moveUp = true;
		}


		// GUI

		auto ptr = pauseButton.getComponent<ButtonComponent>();
		if (!AppData::getInput().isMouseLocked()) { ptr->update(); }
		if (ptr->isClicked()) {
			auto next = std::shared_ptr<Scene>(new LevelSelectionScene());
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(shared_from_this(), next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
		}
		if (ptr->isHovered()) {
			pauseButton.getComponent<VisualComponent>()->setTexture("menu_pressed");
		}
		else { pauseButton.getComponent<VisualComponent>()->setTexture("menu_not_pressed"); }

		ptr = replayButton.getComponent<ButtonComponent>();
		if (!AppData::getInput().isMouseLocked()) { ptr->update(); }
		if (ptr->isClicked() || ball.getComponent<DynamicPhysicsComponent>()->exploded()) {
			auto next = std::shared_ptr<Scene>(new LevelTwoScene());
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(shared_from_this(), next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
		}
		if (ptr->isHovered()) {
			replayButton.getComponent<VisualComponent>()->setTexture("replay_pressed");
		}
		else { replayButton.getComponent<VisualComponent>()->setTexture("replay_not_pressed"); }

		ptr = camLockButton.getComponent<ButtonComponent>();
		if (!AppData::getInput().isMouseLocked()) { ptr->update(); }
		if (ptr->isClicked()) {
			camLocked = !camLocked;
		}
		if (ptr->isHovered()) {
			if (camLocked) { camLockButton.getComponent<VisualComponent>()->setTexture("cam_locked_pressed"); }
			else { camLockButton.getComponent<VisualComponent>()->setTexture("cam_unlocked_pressed"); }
		}
		else {
			if (camLocked) { camLockButton.getComponent<VisualComponent>()->setTexture("cam_locked_not_pressed"); }
			else { camLockButton.getComponent<VisualComponent>()->setTexture("cam_unlocked_not_pressed"); }
		}


		firstDigit.getComponent<VisualComponent>()->setTexture(std::to_string(score % 10));
		secondDigit.getComponent<VisualComponent>()->setTexture(std::to_string((score % 100) / 10));


		if (score > 9) {
			stars = 0;
		}
		else if (score > 5) {
			stars = 1;
		}
		else if (score > 2) {
			stars = 2;
		}

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

		// Logika zakonczenia poziomu
		if (AppData::getInput().isKeyPressed("P") || won) {
			score--;
			if (score > 9) {
				stars = 0;
			}
			else if (score > 5) {
				stars = 1;
			}
			else if (score > 2) {
				stars = 2;
			}
			else {
				stars = 3;
			}
			auto next = std::shared_ptr<Scene>(new ResultsScene(score, stars, 2));
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(shared_from_this(), next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
			score++;
		}

		
	}

	void LevelTwoScene::render() {
		background.render();
		m_graphicsLayer.draw();
		guiLayer.render();
	}

	// ===============================
	// LevelThreeScene
	// ===============================

	LevelThreeScene::LevelThreeScene()
		:m_graphicsLayer(*AppData::getSus().GetShader("DefaultShader.glsl"), m_camera),
		cameraControls(m_camera, 0.f, 8.f, 6.f, 0.f) {
		AppData::getInput().attachCamera(&m_camera, 10.0f);

		grass.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		grass.getComponent<VisualComponent>()->setTexture("Grass");
		grass.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		grass.getTransform()->setScale(8.0f, 8.0f);
		grass.getTransform()->setPos(4, 3);

		frame1.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame1.getComponent<VisualComponent>()->setColor(87, 34, 18, 255);
		frame1.getTransform()->setPos(0.0f, 3.0f);
		frame1.getTransform()->setScale(0.2f, 8.2f);
		frame1.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		frame1.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		frame2.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame2.getComponent<VisualComponent>()->setColor(87, 34, 18, 255);
		frame2.getTransform()->setPos(4.0f, 7.0f);
		frame2.getTransform()->setScale(8.0f, 0.2f);
		frame2.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		frame2.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		frame3.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame3.getComponent<VisualComponent>()->setColor(87, 34, 18, 255);
		frame3.getTransform()->setPos(8.1f, 3.0f);
		frame3.getTransform()->setScale(0.2f, 8.2f);
		frame3.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		frame3.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		frame4.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame4.getComponent<VisualComponent>()->setColor(87, 34, 18, 255);
		frame4.getTransform()->setPos(4.0f, -1.0f);
		frame4.getTransform()->setScale(8.0f, 0.2f);
		frame4.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		frame4.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		const float rotateSpeed = 0.7f;
		wallA.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		wallA.getComponent<VisualComponent>()->setTexture("Wood");
		wallA.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		wallA.getTransform()->setPos(4.0f, 3.0f);
		wallA.getTransform()->setScale(6.0f, 0.2f);
		wallA.addComponent<KinematicPhysicsComponent>(physics.addKinematicElement());
		wallA.getComponent<KinematicPhysicsComponent>()->m_angular_velocity = {0, 0, rotateSpeed};
		wallA.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		wallB.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		wallB.getComponent<VisualComponent>()->setTexture("Wood");
		wallB.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		wallB.getTransform()->setPos(4.0f, 3.0f);
		wallB.getTransform()->setScale(0.2f, 6.0f);
		wallB.addComponent<KinematicPhysicsComponent>(physics.addKinematicElement());
		wallB.getComponent<KinematicPhysicsComponent>()->m_angular_velocity = { 0, 0, rotateSpeed };
		wallB.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		hole.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		hole.getComponent<VisualComponent>()->setTexture("hole");
		hole.getTransform()->setPos(7.0f, 5.0f);
		hole.getTransform()->setScale(0.5f);

		ball.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		ball.getComponent<VisualComponent>()->setTexture("Ball");
		ball.getTransform()->setPos(1.0f, 1.0f);
		ball.getTransform()->setScale(0.2f);
		ball.addComponent<DynamicPhysicsComponent>(physics.addDynamicElement(0.1f, 0.001f));
		ball.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Kula, 0.1f));
		ball.addComponent<SlingshotComponent>(std::make_shared<SlingshotComponent>(m_camera, m_graphicsLayer));

		/////////////////
		// GUI
		/////////////////

		pauseButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		pauseButton.getComponent<GUIComponent>()->setPosition(PositionType::TOPRIGHT, -0.05f, -0.05f, ModeType::RELATIVE);
		pauseButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		pauseButton.getTransform()->setScale(0.1f, 0.1f);
		pauseButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		replayButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		replayButton.getComponent<GUIComponent>()->setPosition(PositionType::TOPRIGHT, -0.05f, -0.16f, ModeType::RELATIVE);
		replayButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		replayButton.getTransform()->setScale(0.1f, 0.1f);
		replayButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		camLockButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		camLockButton.getComponent<GUIComponent>()->setPosition(PositionType::TOPRIGHT, -0.05f, -0.27f, ModeType::RELATIVE);
		camLockButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		camLockButton.getTransform()->setScale(0.1f, 0.1f);
		camLockButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		firstDigit.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		firstDigit.getComponent<GUIComponent>()->setPosition(PositionType::TOPLEFT, 0.105f, -0.05f, ModeType::RELATIVE);
		firstDigit.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		firstDigit.getTransform()->setScale(0.1f, 0.1f);
		firstDigit.getComponent<VisualComponent>()->setTexture("0");

		secondDigit.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		secondDigit.getComponent<GUIComponent>()->setPosition(PositionType::TOPLEFT, 0.05f, -0.05f, ModeType::RELATIVE);
		secondDigit.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		secondDigit.getTransform()->setScale(0.1f, 0.1f);
		secondDigit.getComponent<VisualComponent>()->setTexture("0");

		starDisplay.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		starDisplay.getComponent<GUIComponent>()->setPosition(PositionType::TOPLEFT, 0.045f, -0.11f, ModeType::RELATIVE);
		starDisplay.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		starDisplay.getTransform()->setScale(0.17f, 0.0633f);
	}

	void LevelThreeScene::update(float deltaT)
	{
		// camera
		if (!camLocked) {
			if (ball.getComponent<DynamicPhysicsComponent>()->isMoving()) {
				cameraControls.follow(ball.getTransform()->x, ball.getTransform()->y);
			}
		}
		else {
			cameraControls.lock(4.f, 3.f, 0.8f);
		}
		cameraControls.update(deltaT);

		// ball
		ball.getComponent<SlingshotComponent>()->update(deltaT);
		if(ball.getComponent<SlingshotComponent>()->didShoot()) {
			score++;
		}

		// hole logic
		{
			float ballX = ball.getTransform()->x;
			float ballY = ball.getTransform()->y;
			float holeX = hole.getTransform()->x;
			float holeY = hole.getTransform()->y;
			GML::Vec3f dist = { holeX - ballX, holeY - ballY, 0 };
			uchar color = 255;
			if (dist.getLengthSquared() < hole.getTransform()->xScale * hole.getTransform()->xScale / 3) {
				ball.getComponent<DynamicPhysicsComponent>()->apply_force(5 * dist, { 0, 0, 0 });
				ball.getComponent<DynamicPhysicsComponent>()->apply_force(-1 * static_cast<GML::Vec3f>(ball.getComponent<DynamicPhysicsComponent>()->m_velocity), { 0, 0, 0 });
				float col = util::lerp(-50, 255, dist.getLength() / hole.getTransform()->xScale * 2);
				color = static_cast<uchar>(util::clamp(col, 0, 255));
				if (col < 0 && ball.getComponent<DynamicPhysicsComponent>()->m_velocity.getLength() < 0.03f) {
					won = true;
				}
			}
			ball.getComponent<VisualComponent>()->setColor(255, 255, 255, color);
		}

		physics.update(deltaT);

		// GUI

		auto ptr = pauseButton.getComponent<ButtonComponent>();
		if (!AppData::getInput().isMouseLocked()) { ptr->update(); }
		if (ptr->isClicked()) {
			auto next = std::shared_ptr<Scene>(new LevelSelectionScene());
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(shared_from_this(), next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
		}
		if (ptr->isHovered()) {
			pauseButton.getComponent<VisualComponent>()->setTexture("menu_pressed");
		}
		else { pauseButton.getComponent<VisualComponent>()->setTexture("menu_not_pressed"); }

		ptr = replayButton.getComponent<ButtonComponent>();
		if (!AppData::getInput().isMouseLocked()) { ptr->update(); }
		if (ptr->isClicked() || ball.getComponent<DynamicPhysicsComponent>()->exploded()) {
			AppData::getInput().setMousePosLock(false);
			auto next = std::shared_ptr<Scene>(new LevelThreeScene());
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(shared_from_this(), next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
		}
		if (ptr->isHovered()) {
			replayButton.getComponent<VisualComponent>()->setTexture("replay_pressed");
		}
		else { replayButton.getComponent<VisualComponent>()->setTexture("replay_not_pressed"); }

		ptr = camLockButton.getComponent<ButtonComponent>();
		if (!AppData::getInput().isMouseLocked()) { ptr->update(); }
		if (ptr->isClicked()) {
			camLocked = !camLocked;
		}
		if (ptr->isHovered()) {
			if (camLocked) { camLockButton.getComponent<VisualComponent>()->setTexture("cam_locked_pressed"); }
			else { camLockButton.getComponent<VisualComponent>()->setTexture("cam_unlocked_pressed"); }
		}
		else {
			if (camLocked) { camLockButton.getComponent<VisualComponent>()->setTexture("cam_locked_not_pressed"); }
			else { camLockButton.getComponent<VisualComponent>()->setTexture("cam_unlocked_not_pressed"); }
		}


		firstDigit.getComponent<VisualComponent>()->setTexture(std::to_string(score % 10));
		secondDigit.getComponent<VisualComponent>()->setTexture(std::to_string((score % 100) / 10));


		if (score > 9) {
			stars = 0;
		}
		else if (score > 5) {
			stars = 1;
		}
		else if (score > 2) {
			stars = 2;
		}

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

		// Logika zakonczenia poziomu
		if (AppData::getInput().isKeyPressed("P") || won) {
			score--;
			if (score > 9) {
				stars = 0;
			}
			else if (score > 5) {
				stars = 1;
			}
			else if (score > 2) {
				stars = 2;
			}
			else {
				stars = 3;
			}
			auto next = std::shared_ptr<Scene>(new ResultsScene(score, stars, 3));
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(shared_from_this(), next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
			score++;
		}
	}

	void LevelThreeScene::render()
	{
		background.render();
		m_graphicsLayer.draw();
		guiLayer.render();
	}


	// ===============================
	// LevelFourScene
	// ===============================

	LevelFourScene::LevelFourScene()
		:m_graphicsLayer(*AppData::getSus().GetShader("DefaultShader.glsl"), m_camera),
		cameraControls(m_camera, -5.f, 5.f, 2.f, -10.f) {
		AppData::getInput().attachCamera(&m_camera, 10.0f);

		grass.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		grass.getComponent<VisualComponent>()->setTexture("Grass");
		grass.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		grass.getTransform()->setScale(7.6f, 7);
		grass.getTransform()->setPos(3.85f, -4.5);

		grass2.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		grass2.getComponent<VisualComponent>()->setTexture("Grass");
		grass2.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		grass2.getTransform()->setScale(5.f, 3.f);
		grass2.getTransform()->setPos(2.5f, 0.5f);

		ramp.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		ramp.getComponent<VisualComponent>()->setTexture("carp");
		ramp.getTransform()->setScale(2.7f, 4);
		ramp.getTransform()->setPos(5.4f, -0.3f);
		ramp.getTransform()->rot =45.0f;
		ramp.addComponent<SurfaceComponent>(physics.addSurfaceElement(0.9f, 0.4f));
		
		frame1.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame1.getComponent<VisualComponent>()->setColor(87, 34, 18, 255);
		frame1.getTransform()->setPos(0.0f, -2.9f);
		frame1.getTransform()->setScale(0.2f, 10.0f);
		frame1.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		frame1.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		frame2.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame2.getComponent<VisualComponent>()->setColor(87, 34, 18, 255);
		frame2.getTransform()->setPos(2.5f, 2.0f);
		frame2.getTransform()->setScale(5.0f, 0.2f);
		frame2.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		frame2.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		frame3.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame3.getComponent<VisualComponent>()->setColor(87, 34, 18, 255);
		frame3.getTransform()->setPos(6.35f, 0.6f);
		frame3.getTransform()->setScale(0.2f, 4.0f);
		frame3.getTransform()->rot = 45.0f;
		frame3.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		frame3.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		frame4.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame4.getComponent<VisualComponent>()->setColor(87, 34, 18, 255);
		frame4.getTransform()->setPos(1.5f, 0.0f);
		frame4.getTransform()->setScale(3.0f, 0.2f);
		frame4.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		frame4.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		frame5.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame5.getComponent<VisualComponent>()->setColor(87, 34, 18, 255);
		frame5.getTransform()->setPos(7.75f, -4.35f);
		frame5.getTransform()->setScale( 0.2f, 7.2f);
		frame5.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		frame5.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		frame6.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame6.getComponent<VisualComponent>()->setColor(87, 34, 18, 255);
		frame6.getTransform()->setPos(3.875f, -7.9f);
		frame6.getTransform()->setScale(7.95f,0.2f);
		frame6.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		frame6.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		const float rotateSpeed = 2.f;
		wall1.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		wall1.getComponent<VisualComponent>()->setTexture("Wood");
		wall1.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		wall1.getTransform()->setPos(2.5f, -2.0f);
		wall1.getTransform()->setScale(2.5f, 0.2f);
		wall1.addComponent<KinematicPhysicsComponent>(physics.addKinematicElement());
		wall1.getComponent<KinematicPhysicsComponent>()->m_angular_velocity = { 0, 0, rotateSpeed };
		wall1.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		wall2.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		wall2.getComponent<VisualComponent>()->setTexture("Wood");
		wall2.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		wall2.getTransform()->setPos(5.5f, -3.5f);
		wall2.getTransform()->setScale(2.5f, 0.2f);
		wall2.getTransform()->rot = 20.0f;
		wall2.addComponent<KinematicPhysicsComponent>(physics.addKinematicElement());
		wall2.getComponent<KinematicPhysicsComponent>()->m_angular_velocity = { 0, 0, rotateSpeed };
		wall2.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));


		wall3.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		wall3.getComponent<VisualComponent>()->setTexture("Wood");
		wall3.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		wall3.getTransform()->setPos(2.5f, -5.5f);
		wall3.getTransform()->setScale(2.5f, 0.2f);
		wall3.getTransform()->rot = 100.0f;
		wall3.addComponent<KinematicPhysicsComponent>(physics.addKinematicElement());
		wall3.getComponent<KinematicPhysicsComponent>()->m_angular_velocity = { 0, 0, rotateSpeed };
		wall3.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		//=========
		hole.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		hole.getComponent<VisualComponent>()->setTexture("hole");
		hole.getTransform()->setPos(1.0f, 1.0f);
		hole.getTransform()->setScale(0.5f);

		ball.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		ball.getComponent<VisualComponent>()->setTexture("Ball");
		ball.getTransform()->setPos(1.0f, -7.0f);
		ball.getTransform()->setScale(0.2f);
		ball.addComponent<DynamicPhysicsComponent>(physics.addDynamicElement(0.1f, 0.001f));
		ball.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Kula, 0.1f));
		ball.addComponent<SlingshotComponent>(std::make_shared<SlingshotComponent>(m_camera, m_graphicsLayer));

		/////////////////
		// GUI
		/////////////////

		pauseButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		pauseButton.getComponent<GUIComponent>()->setPosition(PositionType::TOPRIGHT, -0.05f, -0.05f, ModeType::RELATIVE);
		pauseButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		pauseButton.getTransform()->setScale(0.1f, 0.1f);
		pauseButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		replayButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		replayButton.getComponent<GUIComponent>()->setPosition(PositionType::TOPRIGHT, -0.05f, -0.16f, ModeType::RELATIVE);
		replayButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		replayButton.getTransform()->setScale(0.1f, 0.1f);
		replayButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		camLockButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		camLockButton.getComponent<GUIComponent>()->setPosition(PositionType::TOPRIGHT, -0.05f, -0.27f, ModeType::RELATIVE);
		camLockButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		camLockButton.getTransform()->setScale(0.1f, 0.1f);
		camLockButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		firstDigit.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		firstDigit.getComponent<GUIComponent>()->setPosition(PositionType::TOPLEFT, 0.105f, -0.05f, ModeType::RELATIVE);
		firstDigit.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		firstDigit.getTransform()->setScale(0.1f, 0.1f);
		firstDigit.getComponent<VisualComponent>()->setTexture("0");

		secondDigit.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		secondDigit.getComponent<GUIComponent>()->setPosition(PositionType::TOPLEFT, 0.05f, -0.05f, ModeType::RELATIVE);
		secondDigit.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		secondDigit.getTransform()->setScale(0.1f, 0.1f);
		secondDigit.getComponent<VisualComponent>()->setTexture("0");

		starDisplay.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		starDisplay.getComponent<GUIComponent>()->setPosition(PositionType::TOPLEFT, 0.045f, -0.11f, ModeType::RELATIVE);
		starDisplay.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		starDisplay.getTransform()->setScale(0.17f, 0.0633f);
	}

	void LevelFourScene::update(float deltaT)
	{

		// camera
		if (!camLocked) {
			if (ball.getComponent<DynamicPhysicsComponent>()->isMoving()) {
				cameraControls.follow(ball.getTransform()->x, ball.getTransform()->y);
			}
		}
		else {
			cameraControls.lock(4.f, -3.0f, 1.0f);
		}
		cameraControls.update(deltaT);

		// ball
		ball.getComponent<SlingshotComponent>()->update(deltaT);
		if(ball.getComponent<SlingshotComponent>()->didShoot()) {
			score++;
		}

		// hole logic
		{
			float ballX = ball.getTransform()->x;
			float ballY = ball.getTransform()->y;
			float holeX = hole.getTransform()->x;
			float holeY = hole.getTransform()->y;
			GML::Vec3f dist = { holeX - ballX, holeY - ballY, 0 };
			uchar color = 255;
			if (dist.getLengthSquared() < hole.getTransform()->xScale * hole.getTransform()->xScale / 3) {
				ball.getComponent<DynamicPhysicsComponent>()->apply_force(5 * dist, { 0, 0, 0 });
				ball.getComponent<DynamicPhysicsComponent>()->apply_force(-1 * static_cast<GML::Vec3f>(ball.getComponent<DynamicPhysicsComponent>()->m_velocity), { 0, 0, 0 });
				float col = util::lerp(-50, 255, dist.getLength() / hole.getTransform()->xScale * 2);
				color = static_cast<uchar>(util::clamp(col, 0, 255));
				if (col < 0 && ball.getComponent<DynamicPhysicsComponent>()->m_velocity.getLength() < 0.03f) {
					won = true;
				}
			}
			ball.getComponent<VisualComponent>()->setColor(255, 255, 255, color);
		}

		physics.update(deltaT);

		// GUI

		auto ptr = pauseButton.getComponent<ButtonComponent>();
		if (!AppData::getInput().isMouseLocked()) { ptr->update(); }
		if (ptr->isClicked()) {
			auto next = std::shared_ptr<Scene>(new LevelSelectionScene());
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(shared_from_this(), next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
		}
		if (ptr->isHovered()) {
			pauseButton.getComponent<VisualComponent>()->setTexture("menu_pressed");
		}
		else { pauseButton.getComponent<VisualComponent>()->setTexture("menu_not_pressed"); }

		ptr = replayButton.getComponent<ButtonComponent>();
		if (!AppData::getInput().isMouseLocked()) { ptr->update(); }
		if (ptr->isClicked() || ball.getComponent<DynamicPhysicsComponent>()->exploded()) {
			AppData::getInput().setMousePosLock(false);
			auto next = std::shared_ptr<Scene>(new LevelFourScene());
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(shared_from_this(), next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
		}
		if (ptr->isHovered()) {
			replayButton.getComponent<VisualComponent>()->setTexture("replay_pressed");
		}
		else { replayButton.getComponent<VisualComponent>()->setTexture("replay_not_pressed"); }

		ptr = camLockButton.getComponent<ButtonComponent>();
		if (!AppData::getInput().isMouseLocked()) { ptr->update(); }
		if (ptr->isClicked()) {
			camLocked = !camLocked;
		}
		if (ptr->isHovered()) {
			if (camLocked) { camLockButton.getComponent<VisualComponent>()->setTexture("cam_locked_pressed"); }
			else { camLockButton.getComponent<VisualComponent>()->setTexture("cam_unlocked_pressed"); }
		}
		else {
			if (camLocked) { camLockButton.getComponent<VisualComponent>()->setTexture("cam_locked_not_pressed"); }
			else { camLockButton.getComponent<VisualComponent>()->setTexture("cam_unlocked_not_pressed"); }
		}


		firstDigit.getComponent<VisualComponent>()->setTexture(std::to_string(score % 10));
		secondDigit.getComponent<VisualComponent>()->setTexture(std::to_string((score % 100) / 10));


		if (score > 9) {
			stars = 0;
		}
		else if (score > 5) {
			stars = 1;
		}
		else if (score > 2) {
			stars = 2;
		}

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

		// Logika zakonczenia poziomu
		if (AppData::getInput().isKeyPressed("P") || won) {
			score--;
			if (score > 9) {
				stars = 0;
			}
			else if (score > 5) {
				stars = 1;
			}
			else if (score > 2) {
				stars = 2;
			}
			else {
				stars = 3;
			}
			auto next = std::shared_ptr<Scene>(new ResultsScene(score, stars, 4));
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(shared_from_this(), next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
			score++;
		}
	}

	void LevelFourScene::render() {
		background.render();
		m_graphicsLayer.draw();
		guiLayer.render();
	}

	// ===============================
	// LevelFiveScene
	// ===============================

	LevelFiveScene::LevelFiveScene()
		: m_graphicsLayer(*AppData::getSus().GetShader("DefaultShader.glsl"), m_camera),
		cameraControls(m_camera, 2.f, 14.f, 10.f, 0.f) {
		AppData::getInput().attachCamera(&m_camera, 10.0f);

		grass.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		grass.getComponent<VisualComponent>()->setTexture("Grass");
		grass.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		grass.getTransform()->setScale(16.0f, 12.0f);
		grass.getTransform()->setPos(8, 6);

		wallB.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		wallB.getComponent<VisualComponent>()->setTexture("Wood");
		wallB.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		wallB.getTransform()->setPos(6.0f, 6.0f);
		wallB.getTransform()->setScale(12.0f, 1.f);
		wallB.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		wallB.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		const float rotateSpeed = 1.5f;
		w1.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		w1.getComponent<VisualComponent>()->setTexture("Wood");
		w1.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		w1.getTransform()->setPos(5.0f, 9.2f);
		w1.getTransform()->setScale(4.0f, 0.2f);
		w1.addComponent<KinematicPhysicsComponent>(physics.addKinematicElement());
		w1.getComponent<KinematicPhysicsComponent>()->m_angular_velocity = { 0, 0, rotateSpeed };
		w1.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		w2.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		w2.getComponent<VisualComponent>()->setTexture("Wood");
		w2.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		w2.getTransform()->setPos(5.0f, 9.2f);
		w2.getTransform()->setScale(0.2f, 4.0f);
		w2.addComponent<KinematicPhysicsComponent>(physics.addKinematicElement());
		w2.getComponent<KinematicPhysicsComponent>()->m_angular_velocity = { 0, 0, rotateSpeed };
		w2.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		w3.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		w3.getComponent<VisualComponent>()->setTexture("Wood");
		w3.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		w3.getTransform()->setPos(11.0f, 9.2f);
		w3.getTransform()->setScale(4.0f, 0.2f);
		w3.addComponent<KinematicPhysicsComponent>(physics.addKinematicElement());
		w3.getComponent<KinematicPhysicsComponent>()->m_angular_velocity = { 0, 0, -rotateSpeed };
		w3.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		w4.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		w4.getComponent<VisualComponent>()->setTexture("Wood");
		w4.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		w4.getTransform()->setPos(11.0f, 9.2f);
		w4.getTransform()->setScale( 0.2f, 4.0f);
		w4.addComponent<KinematicPhysicsComponent>(physics.addKinematicElement());
		w4.getComponent<KinematicPhysicsComponent>()->m_angular_velocity = { 0, 0, -rotateSpeed };
		w4.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		q1.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		q1.getComponent<VisualComponent>()->setTexture("ramp1");
		q1.getTransform()->setPos(5.0f, 2.2f);
		q1.getTransform()->setScale(1.0f, 2.0f);
		q1.addComponent<KinematicPhysicsComponent>(physics.addKinematicElement());
		q1.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));


		q2.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		q2.getComponent<VisualComponent>()->setTexture("ramp1");
		q2.getTransform()->setPos(8.0f, 2.7f);
		q2.getTransform()->setScale(1.0f, 2.0f);
		q2.addComponent<KinematicPhysicsComponent>(physics.addKinematicElement());
		q2.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));


		q3.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		q3.getComponent<VisualComponent>()->setTexture("ramp1");
		q3.getTransform()->setPos(11.0f, 3.3f);
		q3.getTransform()->setScale(1.0f, 2.0f);
		q3.addComponent<KinematicPhysicsComponent>(physics.addKinematicElement());
		q3.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));


		frame1.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame1.getComponent<VisualComponent>()->setColor(87, 34, 18, 255);
		frame1.getTransform()->setPos(0.0f, 6.0f);
		frame1.getTransform()->setScale(0.2f, 12.19f);
		frame1.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		frame1.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		frame2.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame2.getComponent<VisualComponent>()->setColor(87, 34, 18, 255);
		frame2.getTransform()->setPos(8.0f, 12.0f);
		frame2.getTransform()->setScale(16.15f, 0.2f);
		frame2.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		frame2.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		frame3.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame3.getComponent<VisualComponent>()->setColor(87, 34, 18, 255);
		frame3.getTransform()->setPos(16.1f, 6.0f);
		frame3.getTransform()->setScale(0.2f, 12.19f);
		frame3.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		frame3.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		frame4.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		frame4.getComponent<VisualComponent>()->setColor(87, 34, 18, 255);
		frame4.getTransform()->setPos(8.0f, 0.0f);
		frame4.getTransform()->setScale(16.15f, 0.2f);
		frame4.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		frame4.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		//=========
		hole.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		hole.getComponent<VisualComponent>()->setTexture("hole");
		hole.getTransform()->setPos(2.0f, 11.0f);
		hole.getTransform()->setScale(0.5f);

		ball.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		ball.getComponent<VisualComponent>()->setTexture("Ball");
		ball.getTransform()->setPos(2.0f, 2.0f);
		ball.getTransform()->setScale(0.2f);
		ball.addComponent<DynamicPhysicsComponent>(physics.addDynamicElement(0.1f, 0.001f));
		ball.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Kula, 0.1f));
		ball.addComponent<SlingshotComponent>(std::make_shared<SlingshotComponent>(m_camera, m_graphicsLayer));

		/////////////////
		// GUI
		/////////////////

		pauseButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		pauseButton.getComponent<GUIComponent>()->setPosition(PositionType::TOPRIGHT, -0.05f, -0.05f, ModeType::RELATIVE);
		pauseButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		pauseButton.getTransform()->setScale(0.1f, 0.1f);
		pauseButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		replayButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		replayButton.getComponent<GUIComponent>()->setPosition(PositionType::TOPRIGHT, -0.05f, -0.16f, ModeType::RELATIVE);
		replayButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		replayButton.getTransform()->setScale(0.1f, 0.1f);
		replayButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		camLockButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		camLockButton.getComponent<GUIComponent>()->setPosition(PositionType::TOPRIGHT, -0.05f, -0.27f, ModeType::RELATIVE);
		camLockButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		camLockButton.getTransform()->setScale(0.1f, 0.1f);
		camLockButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		firstDigit.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		firstDigit.getComponent<GUIComponent>()->setPosition(PositionType::TOPLEFT, 0.105f, -0.05f, ModeType::RELATIVE);
		firstDigit.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		firstDigit.getTransform()->setScale(0.1f, 0.1f);
		firstDigit.getComponent<VisualComponent>()->setTexture("0");

		secondDigit.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		secondDigit.getComponent<GUIComponent>()->setPosition(PositionType::TOPLEFT, 0.05f, -0.05f, ModeType::RELATIVE);
		secondDigit.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		secondDigit.getTransform()->setScale(0.1f, 0.1f);
		secondDigit.getComponent<VisualComponent>()->setTexture("0");

		starDisplay.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		starDisplay.getComponent<GUIComponent>()->setPosition(PositionType::TOPLEFT, 0.045f, -0.11f, ModeType::RELATIVE);
		starDisplay.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		starDisplay.getTransform()->setScale(0.17f, 0.0633f);
	}

	void LevelFiveScene::update(float deltaT)
	{
		static bool moveUp1 = true;
		static bool moveUp2 = false;
		static bool moveUp3 = true;
		float wallSpeed1 = 1.0f;
		float wallSpeed2 = 2.5f;
		float wallSpeed3 = 3.5f;

		if (moveUp1) {
			q1.getComponent<KinematicPhysicsComponent>()->m_velocity = { 0, wallSpeed1 };
		} else {
			q1.getComponent<KinematicPhysicsComponent>()->m_velocity = { 0, -wallSpeed1 };
		}

		if (moveUp2) {
			q2.getComponent<KinematicPhysicsComponent>()->m_velocity = { 0, wallSpeed2 };
		} else {
			q2.getComponent<KinematicPhysicsComponent>()->m_velocity = { 0, -wallSpeed2 };
		}

		if (moveUp3) {
			q3.getComponent<KinematicPhysicsComponent>()->m_velocity = { 0, wallSpeed3 };
		} else {
			q3.getComponent<KinematicPhysicsComponent>()->m_velocity = { 0, -wallSpeed3 };
		}

		float upperLimit = 4.6f;
		float lowerLimit = 1.1f;

		if (q1.getTransform()->getPos().second >= upperLimit) {
			moveUp1 = false;
		} else if (q1.getTransform()->getPos().second <= lowerLimit) {
			moveUp1 = true;
		}

		if (q2.getTransform()->getPos().second >= upperLimit) {
			moveUp2 = false;
		} else if (q2.getTransform()->getPos().second <= lowerLimit) {
			moveUp2 = true;
		}

		if (q3.getTransform()->getPos().second >= upperLimit) {
			moveUp3 = false;
		} else if (q3.getTransform()->getPos().second <= lowerLimit) {
			moveUp3 = true;
		}

		// camera
		if (!camLocked) {
			if (ball.getComponent<DynamicPhysicsComponent>()->isMoving()) {
				cameraControls.follow(ball.getTransform()->x, ball.getTransform()->y);
			}
		}
		else {
			cameraControls.lock(8.f, 6.f, 1.22f);
		}
		cameraControls.update(deltaT);

		// ball
		ball.getComponent<SlingshotComponent>()->update(deltaT);
		if(ball.getComponent<SlingshotComponent>()->didShoot()) {
			score++;
		}

		// hole logic
		{
			float ballX = ball.getTransform()->x;
			float ballY = ball.getTransform()->y;
			float holeX = hole.getTransform()->x;
			float holeY = hole.getTransform()->y;
			GML::Vec3f dist = { holeX - ballX, holeY - ballY, 0 };
			uchar color = 255;
			if (dist.getLengthSquared() < hole.getTransform()->xScale * hole.getTransform()->xScale / 3) {
				ball.getComponent<DynamicPhysicsComponent>()->apply_force(5 * dist, { 0, 0, 0 });
				ball.getComponent<DynamicPhysicsComponent>()->apply_force(-1 * static_cast<GML::Vec3f>(ball.getComponent<DynamicPhysicsComponent>()->m_velocity), { 0, 0, 0 });
				float col = util::lerp(-50, 255, dist.getLength() / hole.getTransform()->xScale * 2);
				color = static_cast<uchar>(util::clamp(col, 0, 255));
				if (col < 0 && ball.getComponent<DynamicPhysicsComponent>()->m_velocity.getLength() < 0.03f) {
					won = true;
				}
			}
			ball.getComponent<VisualComponent>()->setColor(255, 255, 255, color);
		}

		physics.update(deltaT);

		// GUI

		auto ptr = pauseButton.getComponent<ButtonComponent>();
		if (!AppData::getInput().isMouseLocked()) { ptr->update(); }
		if (ptr->isClicked()) {
			auto next = std::shared_ptr<Scene>(new LevelSelectionScene());
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(shared_from_this(), next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
		}
		if (ptr->isHovered()) {
			pauseButton.getComponent<VisualComponent>()->setTexture("menu_pressed");
		}
		else { pauseButton.getComponent<VisualComponent>()->setTexture("menu_not_pressed"); }

		ptr = replayButton.getComponent<ButtonComponent>();
		if (!AppData::getInput().isMouseLocked()) { ptr->update(); }
		if (ptr->isClicked() || ball.getComponent<DynamicPhysicsComponent>()->exploded()) {
			AppData::getInput().setMousePosLock(false);
			auto next = std::shared_ptr<Scene>(new LevelFiveScene());
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(shared_from_this(), next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
		}
		if (ptr->isHovered()) {
			replayButton.getComponent<VisualComponent>()->setTexture("replay_pressed");
		}
		else { replayButton.getComponent<VisualComponent>()->setTexture("replay_not_pressed"); }

		ptr = camLockButton.getComponent<ButtonComponent>();
		if (!AppData::getInput().isMouseLocked()) { ptr->update(); }
		if (ptr->isClicked()) {
			camLocked = !camLocked;
		}
		if (ptr->isHovered()) {
			if (camLocked) { camLockButton.getComponent<VisualComponent>()->setTexture("cam_locked_pressed"); }
			else { camLockButton.getComponent<VisualComponent>()->setTexture("cam_unlocked_pressed"); }
		}
		else {
			if (camLocked) { camLockButton.getComponent<VisualComponent>()->setTexture("cam_locked_not_pressed"); }
			else { camLockButton.getComponent<VisualComponent>()->setTexture("cam_unlocked_not_pressed"); }
		}

		firstDigit.getComponent<VisualComponent>()->setTexture(std::to_string(score % 10));
		secondDigit.getComponent<VisualComponent>()->setTexture(std::to_string((score % 100) / 10));



		if (score > 9) {
			stars = 0;
		}
		else if (score > 5) {
			stars = 1;
		}
		else if (score > 2) {
			stars = 2;
		}

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

		// Logika zakonczenia poziomu

		if (AppData::getInput().isKeyPressed("P") || won) {
			score--;
			if (score > 9) {
				stars = 0;
			}
			else if (score > 5) {
				stars = 1;
			}
			else if (score > 2) {
				stars = 2;
			}
			else {
				stars = 3;
			}
			auto next = std::shared_ptr<Scene>(new ResultsScene(score, stars, 5));
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(shared_from_this(), next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
			score++;
		}
	}

	void LevelFiveScene::render() {
		background.render();
		m_graphicsLayer.draw();
		guiLayer.render();
	}

	// ===============================
	// LevelSixScene
	// ===============================


	LevelSixScene::LevelSixScene()
		:m_graphicsLayer(*AppData::getSus().GetShader("DefaultShader.glsl"), m_camera),
		cameraControls(m_camera, 0.f, 8.f, 6.f, 0.f)
	{
		AppData::getInput().attachCamera(&m_camera, 10.0f);
		m_camera.setPosition(1.f, 1.f);

		grass.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		grass.getComponent<VisualComponent>()->setTexture("Grass");
		grass.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		grass.getTransform()->setScale(8.0f, 6.0f);
		grass.getTransform()->setPos(4, 3);

		wallA.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		wallA.getComponent<VisualComponent>()->setTexture("Wood");
		wallA.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		wallA.getTransform()->setPos(2.0f, 2.0f);
		wallA.getTransform()->setScale(3.0f, 0.2f);
		wallA.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		wallA.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));
		wallA.getTransform()->rot = 50;

		wallB.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		wallB.getComponent<VisualComponent>()->setTexture("Wood");
		wallB.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		wallB.getTransform()->setPos(5.0f, 4.0f);
		wallB.getTransform()->setScale(2.0f, 0.2f);
		wallB.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		wallB.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));
		wallB.getTransform()->rot = 130;

		wallC.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		wallC.getComponent<VisualComponent>()->setTexture("Wood");
		wallC.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		wallC.getTransform()->setPos(4.0f, 1.0f);
		wallC.getTransform()->setScale(2.0f, 0.2f);
		wallC.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		wallC.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));
		wallC.getTransform()->rot = 130;


		frame1.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		frame1.getComponent<VisualComponent>()->setColor(87, 34, 18, 255);
		frame1.getTransform()->setPos(0.0f, 3.0f);
		frame1.getTransform()->setScale(0.2f, 6.19f);
		frame1.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		frame1.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		frame2.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		frame2.getComponent<VisualComponent>()->setColor(87, 34, 18, 255);
		frame2.getTransform()->setPos(4.0f, 6.0f);
		frame2.getTransform()->setScale(8.15f, 0.2f);
		frame2.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		frame2.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		frame3.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		frame3.getComponent<VisualComponent>()->setColor(87, 34, 18, 255);
		frame3.getTransform()->setPos(8.1f, 3.0f);
		frame3.getTransform()->setScale(0.2f, 6.19f);
		frame3.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		frame3.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		frame4.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		frame4.getComponent<VisualComponent>()->setColor(87, 34, 18, 255);
		frame4.getTransform()->setPos(4.0f, 0.0f);
		frame4.getTransform()->setScale(8.15f, 0.2f);
		frame4.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		frame4.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));




		hole.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		hole.getComponent<VisualComponent>()->setTexture("hole");
		hole.getTransform()->setPos(7.0f, 5.0f);
		hole.getTransform()->setScale(0.5f);

		ball.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		ball.getComponent<VisualComponent>()->setTexture("Ball");
		ball.getTransform()->setPos(1.0f, 1.0f);
		ball.getTransform()->setScale(0.2f);
		ball.addComponent<DynamicPhysicsComponent>(physics.addDynamicElement(0.1f, 0.001f));
		ball.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Kula, 0.1f));
		ball.addComponent<SlingshotComponent>(std::make_shared<SlingshotComponent>(m_camera, m_graphicsLayer));

		/////////////////
		// GUI
		/////////////////

		pauseButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		pauseButton.getComponent<GUIComponent>()->setPosition(PositionType::TOPRIGHT, -0.05f, -0.05f, ModeType::RELATIVE);
		pauseButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		pauseButton.getTransform()->setScale(0.1f, 0.1f);
		pauseButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		replayButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		replayButton.getComponent<GUIComponent>()->setPosition(PositionType::TOPRIGHT, -0.05f, -0.16f, ModeType::RELATIVE);
		replayButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		replayButton.getTransform()->setScale(0.1f, 0.1f);
		replayButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		camLockButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		camLockButton.getComponent<GUIComponent>()->setPosition(PositionType::TOPRIGHT, -0.05f, -0.27f, ModeType::RELATIVE);
		camLockButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		camLockButton.getTransform()->setScale(0.1f, 0.1f);
		camLockButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		firstDigit.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		firstDigit.getComponent<GUIComponent>()->setPosition(PositionType::TOPLEFT, 0.105f, -0.05f, ModeType::RELATIVE);
		firstDigit.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		firstDigit.getTransform()->setScale(0.1f, 0.1f);
		firstDigit.getComponent<VisualComponent>()->setTexture("0");

		secondDigit.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		secondDigit.getComponent<GUIComponent>()->setPosition(PositionType::TOPLEFT, 0.05f, -0.05f, ModeType::RELATIVE);
		secondDigit.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		secondDigit.getTransform()->setScale(0.1f, 0.1f);
		secondDigit.getComponent<VisualComponent>()->setTexture("0");

		starDisplay.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		starDisplay.getComponent<GUIComponent>()->setPosition(PositionType::TOPLEFT, 0.045f, -0.11f, ModeType::RELATIVE);
		starDisplay.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		starDisplay.getTransform()->setScale(0.17f, 0.0633f);
	}

	void LevelSixScene::update(float deltaT)
	{
		// camera
		if (!camLocked) {
			if (ball.getComponent<DynamicPhysicsComponent>()->isMoving()) {
				cameraControls.follow(ball.getTransform()->x, ball.getTransform()->y);
			}
		}
		else {
			cameraControls.lock(4.f, 3.f, 0.65f);
		}
		cameraControls.update(deltaT);

		// ball
		ball.getComponent<SlingshotComponent>()->update(deltaT);
		if(ball.getComponent<SlingshotComponent>()->didShoot()) {
			score++;
		}

		// hole logic
		{
			float ballX = ball.getTransform()->x;
			float ballY = ball.getTransform()->y;
			float holeX = hole.getTransform()->x;
			float holeY = hole.getTransform()->y;
			GML::Vec3f dist = { holeX - ballX, holeY - ballY, 0 };
			uchar color = 255;
			if (dist.getLengthSquared() < hole.getTransform()->xScale * hole.getTransform()->xScale / 3) {
				ball.getComponent<DynamicPhysicsComponent>()->apply_force(5 * dist, { 0, 0, 0 });
				ball.getComponent<DynamicPhysicsComponent>()->apply_force(-1 * static_cast<GML::Vec3f>(ball.getComponent<DynamicPhysicsComponent>()->m_velocity), { 0, 0, 0 });
				float col = util::lerp(-50, 255, dist.getLength() / hole.getTransform()->xScale * 2);
				color = static_cast<uchar>(util::clamp(col, 0, 255));
				if (col < 0 && ball.getComponent<DynamicPhysicsComponent>()->m_velocity.getLength() < 0.03f) {
					won = true;
				}
			}
			ball.getComponent<VisualComponent>()->setColor(255, 255, 255, color);
		}

		physics.update(deltaT);

		// GUI

		auto ptr = pauseButton.getComponent<ButtonComponent>();
		if (!AppData::getInput().isMouseLocked()) { ptr->update(); }
		if (ptr->isClicked()) {
			auto next = std::shared_ptr<Scene>(new LevelSelectionScene());
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(shared_from_this(), next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
		}
		if (ptr->isHovered()) {
			pauseButton.getComponent<VisualComponent>()->setTexture("menu_pressed");
		}
		else { pauseButton.getComponent<VisualComponent>()->setTexture("menu_not_pressed"); }

		ptr = replayButton.getComponent<ButtonComponent>();
		if (!AppData::getInput().isMouseLocked()) { ptr->update(); }
		if (ptr->isClicked() || ball.getComponent<DynamicPhysicsComponent>()->exploded()) {
			AppData::getInput().setMousePosLock(false);
			auto next = std::shared_ptr<Scene>(new LevelSixScene());
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(shared_from_this(), next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
		}
		if (ptr->isHovered()) {
			replayButton.getComponent<VisualComponent>()->setTexture("replay_pressed");
		}
		else { replayButton.getComponent<VisualComponent>()->setTexture("replay_not_pressed"); }

		ptr = camLockButton.getComponent<ButtonComponent>();
		if (!AppData::getInput().isMouseLocked()) { ptr->update(); }
		if (ptr->isClicked()) {
			camLocked = !camLocked;
		}
		if (ptr->isHovered()) {
			if (camLocked) { camLockButton.getComponent<VisualComponent>()->setTexture("cam_locked_pressed"); }
			else { camLockButton.getComponent<VisualComponent>()->setTexture("cam_unlocked_pressed"); }
		}
		else {
			if (camLocked) { camLockButton.getComponent<VisualComponent>()->setTexture("cam_locked_not_pressed"); }
			else { camLockButton.getComponent<VisualComponent>()->setTexture("cam_unlocked_not_pressed"); }
		}


		firstDigit.getComponent<VisualComponent>()->setTexture(std::to_string(score % 10));
		secondDigit.getComponent<VisualComponent>()->setTexture(std::to_string((score % 100) / 10));


		if (score > 12) {
			stars = 0;
		}
		else if (score > 8) {
			stars = 1;
		}
		else if (score > 4) {
			stars = 2;
		}

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

		// Logika zakonczenia poziomu

		if (AppData::getInput().isKeyPressed("P") || won) {
			score--;
			if (score > 12) {
				stars = 0;
			}
			else if (score > 8) {
				stars = 1;
			}
			else if (score > 4) {
				stars = 2;
			}
			else {
				stars = 3;
			}
			auto next = std::shared_ptr<Scene>(new ResultsScene(score, stars, 6));
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(shared_from_this(), next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
			score++;
		}
	}

	void LevelSixScene::render()
	{
		background.render();
		m_graphicsLayer.draw();
		guiLayer.render();
	}
}


//NOLINTEND(readability-function-cognitive-complexity)
