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
				ball.getComponent<DynamicPhysicsComponent>()->apply_force(10 * dist, { 0, 0, 0 });
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

		if (score > 7) {
			stars = 0;
		}
		else if (score > 4) {
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
			if (score > 7) {
				stars = 0;
			}
			else if (score > 4) {
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


		wallA.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		wallA.getComponent<VisualComponent>()->setTexture("Wood");
		wallA.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		wallA.getTransform()->setPos(2.5f, 3.0f);
		wallA.getTransform()->setScale(0.2f, 2.0f);
		wallA.addComponent<KinematicPhysicsComponent>(physics.addKinematicElement());
		wallA.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		wallB.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		wallB.getComponent<VisualComponent>()->setTexture("Wood");
		wallB.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		wallB.getTransform()->setPos(5.5f, 3.0f);
		wallB.getTransform()->setScale(0.2f, 2.0f);
		wallB.addComponent<KinematicPhysicsComponent>(physics.addKinematicElement());
		wallB.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		spikesBlock.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		spikesBlock.getComponent<VisualComponent>()->setTexture("Lava");
		spikesBlock.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		spikesBlock.getTransform()->setPos(4.0f, 3.0f);
		spikesBlock.getTransform()->setScale(1.5f, 2.5f);
		spikesBlock.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		spikesBlock.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f, true));

		wall1.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		wall1.getComponent<VisualComponent>()->setTexture("Wood");
		wall1.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		wall1.getTransform()->setPos(0.8f, 5.2f);
		wall1.getTransform()->setScale(0.2f, 2.2f);
		wall1.getTransform()->rot = -45.f;
		wall1.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		wall1.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		wall2.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		wall2.getComponent<VisualComponent>()->setTexture("Wood");
		wall2.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		wall2.getTransform()->setPos(7.3f, 0.8f);
		wall2.getTransform()->setScale(0.2f, 2.2f);
		wall2.getTransform()->rot = -45.f;
		wall2.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		wall2.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		wall3.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		wall3.getComponent<VisualComponent>()->setTexture("Wood");
		wall3.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		wall3.getTransform()->setPos(6.35f, 5.65f);
		wall3.getTransform()->setScale(0.7f, 0.7f);
		wall3.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		wall3.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		wall4.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		wall4.getComponent<VisualComponent>()->setTexture("Wood");
		wall4.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		wall4.getTransform()->setPos(6.35f, 4.35f);
		wall4.getTransform()->setScale(0.7f, 0.7f);
		wall4.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		wall4.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		wall5.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		wall5.getComponent<VisualComponent>()->setTexture("Wood");
		wall5.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		wall5.getTransform()->setPos(7.65f, 4.35f);
		wall5.getTransform()->setScale(0.7f, 0.7f);
		wall5.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		wall5.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));


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
				ball.getComponent<DynamicPhysicsComponent>()->apply_force(10 * dist, { 0, 0, 0 });
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

		const float wallSpeed = 3.f;
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


		if (score > 5) {
			stars = 0;
		}
		else if (score > 3) {
			stars = 1;
		}
		else if (score > 1) {
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
			if (score > 5) {
				stars = 0;
			}
			else if (score > 3) {
				stars = 1;
			}
			else if (score > 1) {
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
		cameraControls(m_camera, 0.f, 8.f, 7.f, -1.f) {
		AppData::getInput().attachCamera(&m_camera, 10.0f);

		grass.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		grass.getComponent<VisualComponent>()->setTexture("Grass");
		grass.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		grass.getTransform()->setScale(8.0f, 8.0f);
		grass.getTransform()->setPos(4, 3);

		ice.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		ice.getComponent<VisualComponent>()->setTexture("ice");
		ice.getComponent<VisualComponent>()->setTexRepeat(1.f);
		ice.getTransform()->setScale(4.5f, 1.0f);
		ice.getTransform()->setPos(5.75f, -0.5f);
		ice.addComponent<SurfaceComponent>(physics.addSurfaceElement(0.09f, 0.01f));

		sand.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		sand.getComponent<VisualComponent>()->setTexture("carp");
		sand.getComponent<VisualComponent>()->setTexRepeat(1.f);
		sand.getTransform()->setScale(1.0f, 4.5f);
		sand.getTransform()->setPos(.5f, 4.75f);
		sand.addComponent<SurfaceComponent>(physics.addSurfaceElement(1.5f, 0.4f));

		wall1.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		wall1.getComponent<VisualComponent>()->setTexture("Wood");
		wall1.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		wall1.getTransform()->setPos(5.0f, 0.0f);
		wall1.getTransform()->setScale(3.0f, 0.2f);
		wall1.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		wall1.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		wall2.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		wall2.getComponent<VisualComponent>()->setTexture("Wood");
		wall2.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		wall2.getTransform()->setPos(1.0f, 4.0f);
		wall2.getTransform()->setScale(0.2f, 3.0f);
		wall2.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		wall2.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		wall3.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		wall3.getComponent<VisualComponent>()->setTexture("Wood");
		wall3.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		wall3.getTransform()->setPos(7.75f, 0.0f);
		wall3.getTransform()->setScale(0.5f, 0.2f);
		wall3.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		wall3.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		wall4.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		wall4.getComponent<VisualComponent>()->setTexture("Wood");
		wall4.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		wall4.getTransform()->setPos(1.0f, 6.75f);
		wall4.getTransform()->setScale(0.2f, 0.5f);
		wall4.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		wall4.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));


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
		hole.getTransform()->setPos(7.0f, 6.0f);
		hole.getTransform()->setScale(0.5f);

		ball.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		ball.getComponent<VisualComponent>()->setTexture("Ball");
		ball.getTransform()->setPos(0.5f, -0.5f);
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
				ball.getComponent<DynamicPhysicsComponent>()->apply_force(10 * dist, { 0, 0, 0 });
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


		if (score > 8) {
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
			if (score > 8) {
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
		IMGUI_CALL(ImGui::Begin("Debug"));
		IMGUI_CALL(ImGui::SliderFloat("x1", &wall1.getTransform()->x, 5.f, 8.0f););
		IMGUI_CALL(ImGui::SliderFloat("y1", &wall1.getTransform()->y, 3.f, 8.0f););
		IMGUI_CALL(ImGui::SliderFloat("x2", &wall2.getTransform()->x, 5.f, 8.0f););
		IMGUI_CALL(ImGui::SliderFloat("y2", &wall2.getTransform()->y, 3.f, 8.0f););
		IMGUI_CALL(ImGui::End());
		background.render();
		m_graphicsLayer.draw();
		guiLayer.render();
	}


	// ===============================
	// LevelFourScene
	// ===============================

	LevelFourScene::LevelFourScene()
		:m_graphicsLayer(*AppData::getSus().GetShader("DefaultShader.glsl"), m_camera),
		cameraControls(m_camera, 0.f, 7.f, 2.f, -8.f) {
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
		ramp.getComponent<VisualComponent>()->setTexRepeat(1.f);
		ramp.getTransform()->setScale(2.75f, 4);
		ramp.getTransform()->setPos(5.47f, -0.34f);
		ramp.getTransform()->rot =45.0f;
		ramp.addComponent<SurfaceComponent>(physics.addSurfaceElement(1.5f, 0.4f));

		lava.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		lava.getComponent<VisualComponent>()->setTexture("Lava");
		lava.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		lava.getTransform()->setPos(7.6f, -6.4f);
		lava.getTransform()->setScale(0.4f, 3.0f);
		lava.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		lava.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f, true));
		
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
				ball.getComponent<DynamicPhysicsComponent>()->apply_force(10 * dist, { 0, 0, 0 });
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


		if (score > 8) {
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
		cameraControls(m_camera, 0.f, 16.f, 12.f, 0.f) {
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

		wall1.addComponent<VisualComponent>(std::make_shared<VisualComponent>(&m_graphicsLayer));
		wall1.getComponent<VisualComponent>()->setTexture("Wood");
		wall1.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		wall1.getTransform()->setPos(15.13f, 0.92f);
		wall1.getTransform()->setScale(2.7f, 0.2f);
		wall1.getTransform()->rot = 45.f;
		wall1.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		wall1.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		ice1.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		ice1.getComponent<VisualComponent>()->setTexture("ice");
		ice1.getComponent<VisualComponent>()->setTexRepeat(1.f);
		ice1.getTransform()->setScale(7.0f, 3.0f);
		ice1.getTransform()->setPos(8.0f, 4.0f);
		ice1.addComponent<SurfaceComponent>(physics.addSurfaceElement(0.09f, 0.01f));

		sand1.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		sand1.getComponent<VisualComponent>()->setTexture("carp");
		sand1.getComponent<VisualComponent>()->setTexRepeat(1.f);
		sand1.getTransform()->setScale(7.0f, 2.5f);
		sand1.getTransform()->setPos(8.0f, 1.25f);
		sand1.addComponent<SurfaceComponent>(physics.addSurfaceElement(1.5f, 0.4f));

		ice2.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		ice2.getComponent<VisualComponent>()->setTexture("ice");
		ice2.getComponent<VisualComponent>()->setTexRepeat(1.f);
		ice2.getTransform()->setScale(3.5f, 2.75f);
		ice2.getTransform()->setPos(5.5f, 10.625f);
		ice2.addComponent<SurfaceComponent>(physics.addSurfaceElement(0.09f, 0.01f));

		sand2.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		sand2.getComponent<VisualComponent>()->setTexture("carp");
		sand2.getComponent<VisualComponent>()->setTexRepeat(1.f);
		sand2.getTransform()->setScale(3.5f, 2.75f);
		sand2.getTransform()->setPos(5.5f, 7.875f);
		sand2.addComponent<SurfaceComponent>(physics.addSurfaceElement(1.5f, 0.4f));

		ice3.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		ice3.getComponent<VisualComponent>()->setTexture("ice");
		ice3.getComponent<VisualComponent>()->setTexRepeat(1.f);
		ice3.getTransform()->setScale(3.5f, 2.75f);
		ice3.getTransform()->setPos(10.0f, 7.875f);
		ice3.addComponent<SurfaceComponent>(physics.addSurfaceElement(0.09f, 0.01f));

		sand3.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		sand3.getComponent<VisualComponent>()->setTexture("carp");
		sand3.getComponent<VisualComponent>()->setTexRepeat(1.f);
		sand3.getTransform()->setScale(3.5f, 2.75f);
		sand3.getTransform()->setPos(10.0f, 10.625f);
		sand3.addComponent<SurfaceComponent>(physics.addSurfaceElement(1.5f, 0.4f));

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
				ball.getComponent<DynamicPhysicsComponent>()->apply_force(10 * dist, { 0, 0, 0 });
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



		if (score > 10) {
			stars = 0;
		}
		else if (score > 7) {
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
			if (score > 10) {
				stars = 0;
			}
			else if (score > 7) {
				stars = 1;
			}
			else if (score > 4) {
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
		AppData::getInput().attachCamera(&m_camera, 15.0f);
		m_camera.setPosition(1.f, 1.f);

		grass.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		grass.getComponent<VisualComponent>()->setTexture("Grass");
		grass.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		grass.getTransform()->setScale(8.0f, 8.0f);
		grass.getTransform()->setPos(4, 4);

		ice.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		ice.getComponent<VisualComponent>()->setTexture("ice");
		ice.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		ice.getTransform()->setPos(1.0f, 3.0f);
		ice.getTransform()->setScale(2.0f, 2.0f);

		lava.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		lava.getComponent<VisualComponent>()->setTexture("Lava");
		lava.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		lava.getTransform()->setPos(0.0f, 7.0f);
		lava.getTransform()->setScale(0.0f, 2.0f);

		wallA.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		wallA.getComponent<VisualComponent>()->setTexture("Wood");
		wallA.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		wallA.getTransform()->setPos(3.0f, 6.0f);
		wallA.getTransform()->setScale(6.0f, 0.2f);
		wallA.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		wallA.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));


		wallB.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		wallB.getComponent<VisualComponent>()->setTexture("Wood");
		wallB.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		wallB.getTransform()->setPos(6.0f, 4.0f);
		wallB.getTransform()->setScale(4.2f, 0.2f);
		wallB.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		wallB.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));
		wallB.getTransform()->rot = 90;

		wallC.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		wallC.getComponent<VisualComponent>()->setTexture("Wood");
		wallC.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		wallC.getTransform()->setPos(4.0f, 2.0f);
		wallC.getTransform()->setScale(4.0f, 0.2f);
		wallC.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		wallC.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));
	


		wallD.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		wallD.getComponent<VisualComponent>()->setTexture("Wood");
		wallD.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		wallD.getTransform()->setPos(2.0f, 3.0f);
		wallD.getTransform()->setScale(2.2f, 0.2f);
		wallD.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		wallD.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));
		wallD.getTransform()->rot = 90;

		wallE.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		wallE.getComponent<VisualComponent>()->setTexture("Wood");
		wallE.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		wallE.getTransform()->setPos(3.0f, 4.0f);
		wallE.getTransform()->setScale(2.2f, 0.2f);
		wallE.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		wallE.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));
	
		gate1.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		gate1.getComponent<VisualComponent>()->setTexture("Wood");
		gate1.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		gate1.getTransform()->setPos(4.0f, 5.0f);
		gate1.getTransform()->setScale(2.0f, 0.2f);
		gate1.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		gate1.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));
		gate1.getTransform()->rot = 90;

		gate2.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		gate2.getComponent<VisualComponent>()->setTexture("Wood");
		gate2.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		gate2.getTransform()->setPos(6.0f, 7.0f);
		gate2.getTransform()->setScale(2.0f, 0.2f);
		gate2.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		gate2.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));
		gate2.getTransform()->rot = 90;


		gate3.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		gate3.getComponent<VisualComponent>()->setTexture("Wood");
		gate3.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		gate3.getTransform()->setPos(2.0f, 5.0f);
		gate3.getTransform()->setScale(2.0f, 0.2f);
		gate3.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		gate3.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));
		gate3.getTransform()->rot = 90;

		gate4.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		gate4.getComponent<VisualComponent>()->setTexture("Wood");
		gate4.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		gate4.getTransform()->setPos(1.0f, 2.0f);
		gate4.getTransform()->setScale(2.0f, 0.2f);
		gate4.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		gate4.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));
		




		frame1.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		frame1.getComponent<VisualComponent>()->setColor(87, 34, 18, 255);
		frame1.getTransform()->setPos(0.0f, 4.0f);
		frame1.getTransform()->setScale(0.2f, 8.19f);
		frame1.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		frame1.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		frame2.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		frame2.getComponent<VisualComponent>()->setColor(87, 34, 18, 255);
		frame2.getTransform()->setPos(4.0f, 8.0f);
		frame2.getTransform()->setScale(8.15f, 0.2f);
		frame2.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		frame2.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		frame3.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		frame3.getComponent<VisualComponent>()->setColor(87, 34, 18, 255);
		frame3.getTransform()->setPos(8.1f, 4.0f);
		frame3.getTransform()->setScale(0.2f, 8.19f);
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
		hole.getTransform()->setPos(3.0f, 3.0f);
		hole.getTransform()->setScale(0.5f);

		ball.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		ball.getComponent<VisualComponent>()->setTexture("Ball");
		ball.getTransform()->setPos(3.0f, 7.0f);
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
		/////////gate 1 i 2////////
		time += deltaT;
		if (time > 1) {
			gate1.getTransform()->setPos(4.0f, 5.0f);
			gate2.getTransform()->setPos(6.0f, 7.0f);
			gate2.getTransform()->rot = 90;
		}
		if (time > 2) {
			gate1.getTransform()->setPos(4.0f, 7.0f);

			gate2.getTransform()->setPos(7.0f, 6.0f);
			gate2.getTransform()->rot = 0;
			time = 0;
		}

		///////GATE 3/////////
		float moveSpeed = 1.0f;
		static bool moveLeft = true;
		if (moveLeft) {
			gate3.getTransform()->setPos(gate3.getTransform()->getPos().first - moveSpeed * deltaT, gate3.getTransform()->getPos().second);
		}
		else {
			gate3.getTransform()->setPos(gate3.getTransform()->getPos().first + moveSpeed * deltaT, gate3.getTransform()->getPos().second);
		}
		float leftLimit = 1.0f;
		float rightLimit = 2.0f;

		if (gate3.getTransform()->getPos().first <= leftLimit) {
			moveLeft = false;
		}
		else if (gate3.getTransform()->getPos().first >= rightLimit) {
			moveLeft = true;
		}
		//////////lawa/////////
		
		if (right) {
		lava.getTransform()->getScale().first += 0.4 * deltaT;
		lava.getTransform()->getPos().first += 0.2 * deltaT;
		}
		if (lava.getTransform()->getPos().first > 4.0f) {
			right = false;
		}
	
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
				ball.getComponent<DynamicPhysicsComponent>()->apply_force(10 * dist, { 0, 0, 0 });
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


		if (score > 6) {
			stars = 0;
		}
		else if (score > 4) {
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
			if (score > 6) {
				stars = 0;
			}
			else if (score > 4) {
				stars = 1;
			}
			else if (score > 2) {
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
