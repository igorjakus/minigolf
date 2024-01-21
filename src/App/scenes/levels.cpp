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
		frame1.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		frame1.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		frame2.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		frame2.getComponent<VisualComponent>()->setTexture("Wood");
		frame2.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		frame2.getTransform()->setPos(4.0f, 6.0f);
		frame2.getTransform()->setScale(8.15f, 0.2f);
		frame2.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		frame2.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		frame3.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		frame3.getComponent<VisualComponent>()->setTexture("Wood");
		frame3.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		frame3.getTransform()->setPos(8.1f, 3.0f);
		frame3.getTransform()->setScale(0.2f, 6.19f);
		frame3.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		frame3.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

		frame4.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		frame4.getComponent<VisualComponent>()->setTexture("Wood");
		frame4.getComponent<VisualComponent>()->setTexRepeat(1.0f);
		frame4.getTransform()->setPos(4.0f, 0.0f);
		frame4.getTransform()->setScale(8.15f, 0.2f);
		frame4.addComponent<StaticPhysicsComponent>(physics.addStaticElement());
		frame4.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Box, 0.f));

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

		hole.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		hole.getComponent<VisualComponent>()->setTexture("sponge");
		hole.getTransform()->setPos(7.0f, 5.0f);
		hole.getTransform()->setScale(0.5f);

		arrowTip.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		arrowTip.getComponent<VisualComponent>()->setTexture("arrow_tip");
		arrowTip.getComponent<VisualComponent>()->setColor(255, 255, 255, 0);
		arrowTip.getTransform()->setScale(0.5f);

		arrowBody.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		arrowBody.getComponent<VisualComponent>()->setTexture("arrow_body");
		arrowBody.getComponent<VisualComponent>()->setColor(255, 255, 255, 0);
		arrowBody.getTransform()->setScale(0.4f);


		trail5.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		trail5.getComponent<VisualComponent>()->setTexture("Ball");
		trail5.getComponent<VisualComponent>()->setColor(255, 255, 255, 0);

		trail4.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		trail4.getComponent<VisualComponent>()->setTexture("Ball");
		trail4.getComponent<VisualComponent>()->setColor(255, 255, 255, 0);

		trail3.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		trail3.getComponent<VisualComponent>()->setTexture("Ball");
		trail3.getComponent<VisualComponent>()->setColor(255, 255, 255, 0);

		trail2.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		trail2.getComponent<VisualComponent>()->setTexture("Ball");
		trail2.getComponent<VisualComponent>()->setColor(255, 255, 255, 0);

		trail1.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		trail1.getComponent<VisualComponent>()->setTexture("Ball");
		trail1.getComponent<VisualComponent>()->setColor(255, 255, 255, 0);

		ball.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		ball.getComponent<VisualComponent>()->setTexture("Ball");
		ball.getTransform()->setPos(1.0f, 1.0f);
		ball.getTransform()->setScale(0.2f);
		ball.addComponent<DynamicPhysicsComponent>(physics.addDynamicElement());
		ball.getComponent<DynamicPhysicsComponent>()->m_mass = 0.1f;
		ball.getComponent<DynamicPhysicsComponent>()->m_inertia = 0.005f;
		ball.addComponent<HitboxComponent>(std::make_shared<HitboxComponent>(HitboxComponent::Typ::Kula, 0.1f));
		ballButton.addComponent<VisualComponent>(VisualComponent::create(m_graphicsLayer));
		ballButton.getComponent<VisualComponent>()->setTexture("BallButton");
		ballButton.getComponent<VisualComponent>()->setColor(255, 255, 255, 0);
		ballButton.getTransform()->setScale(0.5f);
		ballButton.addComponent<ButtonComponent>(ButtonComponent::create(m_camera));

		trail1.getTransform()->setScale(ball.getTransform()->xScale * 0.8f);
		trail2.getTransform()->setScale(trail1.getTransform()->xScale * 0.8f);
		trail3.getTransform()->setScale(trail2.getTransform()->xScale * 0.8f);
		trail4.getTransform()->setScale(trail3.getTransform()->xScale * 0.8f);
		trail5.getTransform()->setScale(trail4.getTransform()->xScale * 0.8f);

		/////////////////
		// GUI
		/////////////////

		camUp.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		camUp.getComponent<GUIComponent>()->setPosition(PositionType::TOP, 0.f, 0.f, ModeType::RELATIVE);
		camUp.getTransform()->setScale(1000.f, 0.1f);
		camUp.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		camDown.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		camDown.getComponent<GUIComponent>()->setPosition(PositionType::BOTTOM, 0.f, 0.f, ModeType::RELATIVE);
		camDown.getTransform()->setScale(1000.f, 0.1f);
		camDown.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		camRight.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		camRight.getComponent<GUIComponent>()->setPosition(PositionType::RIGHT, 0.f, 0.f, ModeType::RELATIVE);
		camRight.getTransform()->setScale(0.1f, 1000.f);
		camRight.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		camLeft.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		camLeft.getComponent<GUIComponent>()->setPosition(PositionType::LEFT, 0.f, 0.f, ModeType::RELATIVE);
		camLeft.getTransform()->setScale(0.1f, 1000.f);
		camLeft.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

		pauseButton.addComponent<GUIComponent>(guiLayer.createGUIComponent());
		pauseButton.getComponent<GUIComponent>()->setPosition(PositionType::TOPRIGHT, -0.05f, -0.05f, ModeType::RELATIVE);
		pauseButton.addComponent<VisualComponent>(VisualComponent::create(guiLayer));
		pauseButton.getTransform()->setScale(0.1f, 0.1f);
		pauseButton.addComponent<ButtonComponent>(ButtonComponent::create(guiLayer));

	}

	void LevelOneScene::update(float deltaT)
	{
		// camera

		camUp.getComponent<ButtonComponent>()->update();
		camDown.getComponent<ButtonComponent>()->update();
		camRight.getComponent<ButtonComponent>()->update();
		camLeft.getComponent<ButtonComponent>()->update();

		const float cameraSpeed = 10 * m_camera.getFocalLength();
		const float cameraResponse = 30;
		if (AppData::getInput().isKeyPressed("UP") || AppData::getInput().isKeyPressed("W") || (camUp.getComponent<ButtonComponent>()->isHovered() && !aiming)) {
			camUpSpeed += deltaT * cameraResponse;
		} else {
			camUpSpeed -= deltaT * cameraResponse;
		}
		if (AppData::getInput().isKeyPressed("LEFT") || AppData::getInput().isKeyPressed("A") || (camLeft.getComponent<ButtonComponent>()->isHovered() && !aiming)) {
			camLeftSpeed += deltaT * cameraResponse;
		} else {
			camLeftSpeed -= deltaT * cameraResponse;
		}
		if (AppData::getInput().isKeyPressed("RIGHT") || AppData::getInput().isKeyPressed("D") || (camRight.getComponent<ButtonComponent>()->isHovered() && !aiming)) {
			camRightSpeed += deltaT * cameraResponse;
		} else {
			camRightSpeed -= deltaT * cameraResponse;
		}
		if (AppData::getInput().isKeyPressed("DOWN") || AppData::getInput().isKeyPressed("S") || (camDown.getComponent<ButtonComponent>()->isHovered() && !aiming)) {
			camDownSpeed += deltaT * cameraResponse;
		} else {
			camDownSpeed -= deltaT * cameraResponse;
		}

		camUpSpeed = util::clamp(camUpSpeed, 0, cameraSpeed);
		camRightSpeed = util::clamp(camRightSpeed, 0, cameraSpeed);
		camLeftSpeed = util::clamp(camLeftSpeed, 0, cameraSpeed);
		camDownSpeed = util::clamp(camDownSpeed, 0, cameraSpeed);

		float cameraX = m_camera.getPosition().x + deltaT * (camRightSpeed - camLeftSpeed);
		float cameraY = m_camera.getPosition().y + deltaT * (camUpSpeed - camDownSpeed);
		if (ball.getComponent<DynamicPhysicsComponent>()->isMoving()) {
			float c = 0.1f;
			c = 1.f - pow(c, deltaT);
			cameraX = util::lerp(cameraX, ball.getTransform()->x, c);
			cameraY = util::lerp(cameraY, ball.getTransform()->y, c);
			targetZoom = 0.5f;
			zoomTimer = 0.f;
		}
		cameraX = util::clamp(cameraX, camMinX, camMaxX);
		cameraY = util::clamp(cameraY, camMinY, camMaxY);
		m_camera.setPosition(cameraX, cameraY);

		if (AppData::getInput().getWheelOffset() >= 1) {
			targetZoom *= 0.8f;
			zoomTimer = 0;
		}
		if (AppData::getInput().getWheelOffset() <= -1) {
			targetZoom *= 1.25f;
			zoomTimer = 0;
		}
		targetZoom = util::clamp(targetZoom, 0.3f, 1.f);
		zoomTimer += deltaT * 3.f; if (zoomTimer > 1) { zoomTimer = 1; }
		zoom = util::lerp(zoom, targetZoom, zoomTimer);
		m_camera.setFocalLength(zoom);

		// ball
		if (!ball.getComponent<DynamicPhysicsComponent>()->isMoving()) {
			ballButton.getComponent<ButtonComponent>()->update();
			if (ballButton.getComponent<ButtonComponent>()->isHovered() || ballButton.getComponent<ButtonComponent>()->isPressed()) {
				showBallButton = 1.f;
			} else {
				showBallButton -= deltaT * 5.f;
			}
		} else {
			showBallButton = 0.f;
		}

		ballButton.getTransform()->setPos(ball.getTransform()->x, ball.getTransform()->y);
		ballButton.getComponent<VisualComponent>()->setColor(255, 255, 255, static_cast<uchar>(util::clerp(0, 255, showBallButton)));
		ballButton.getTransform()->rot += deltaT * 90.f;

		if (ballButton.getComponent<ButtonComponent>()->isPressed()) {
			aiming = true;
			AppData::getInput().setMousePosLock(true);
		}
		const float maxShotStrength = 2.f;
		if (aiming) {
			auto [x, y] = AppData::getInput().getMouseWorldOffset(m_camera);
			GML::Vec2f pos = { x, y };
			GML::Vec2f norm = pos.normalized();
			float strength = util::clamp(pos.getLength(), 0, maxShotStrength);
			GML::Vec2f val = norm * strength;

			float angle = -std::atan(x / y) * GML::F_RAD_TO_DEG;
			if (y >= 0) { angle += 180; }
			float param = util::norm(0, maxShotStrength, strength);
			uchar red = static_cast<uchar>(util::clerp(150, 230, param));
			uchar green = static_cast<uchar>(util::clerp(255, 0, param));
			arrowTip.getComponent<VisualComponent>()->setColor(red, green, 0, 255);
			arrowTip.getTransform()->rot = angle;
			arrowBody.getComponent<VisualComponent>()->setColor(red, green, 0, 255);
			arrowBody.getTransform()->rot = angle;

			arrowTip.getTransform()->setPos(ball.getTransform()->x + norm.x * (arrowTip.getTransform()->xScale / 2 + 0.1f),
				ball.getTransform()->y + norm.y * (arrowTip.getTransform()->xScale / 2 + 0.1f));
			arrowBody.getTransform()->yScale = val.getLength();
			arrowBody.getTransform()->setPos(ball.getTransform()->x + norm.x * (arrowBody.getTransform()->yScale / 2 + arrowTip.getTransform()->xScale + 0.11f),
				ball.getTransform()->y + norm.y * (arrowBody.getTransform()->yScale / 2 + arrowTip.getTransform()->xScale + 0.11f));

			trail1.getTransform()->setPos(ball.getTransform()->x - 1 * val.x * 0.3f, ball.getTransform()->y - 1 * val.y * 0.3f);
			trail2.getTransform()->setPos(ball.getTransform()->x - 2 * val.x * 0.3f, ball.getTransform()->y - 2 * val.y * 0.3f);
			trail3.getTransform()->setPos(ball.getTransform()->x - 3 * val.x * 0.3f, ball.getTransform()->y - 3 * val.y * 0.3f);
			trail4.getTransform()->setPos(ball.getTransform()->x - 4 * val.x * 0.3f, ball.getTransform()->y - 4 * val.y * 0.3f);
			trail5.getTransform()->setPos(ball.getTransform()->x - 5 * val.x * 0.3f, ball.getTransform()->y - 5 * val.y * 0.3f);

			trail1.getComponent<VisualComponent>()->setColor(255, 255, 255, static_cast<uchar>(255 * 0.8f));
			trail2.getComponent<VisualComponent>()->setColor(255, 255, 255, static_cast<uchar>(255 * 0.8f * 0.8f));
			trail3.getComponent<VisualComponent>()->setColor(255, 255, 255, static_cast<uchar>(255 * 0.8f * 0.8f * 0.8f));
			trail4.getComponent<VisualComponent>()->setColor(255, 255, 255, static_cast<uchar>(255 * 0.8f * 0.8f * 0.8f * 0.8f));
			trail5.getComponent<VisualComponent>()->setColor(255, 255, 255, static_cast<uchar>(255 * 0.8f * 0.8f * 0.8f * 0.8f * 0.8f));

			if (ballButton.getComponent<ButtonComponent>()->isReleased()) {
				AppData::getInput().setMousePosLock(false);
				ballButton.getComponent<ButtonComponent>()->update();
				ball.getComponent<DynamicPhysicsComponent>()->apply_impulse({ -val.x, -val.y, 0 }, { 0, 0, 0 });

				arrowTip.getComponent<VisualComponent>()->setColor(255, 255, 255, 0);
				arrowBody.getComponent<VisualComponent>()->setColor(255, 255, 255, 0);
				trail1.getComponent<VisualComponent>()->setColor(255, 255, 255, 0);
				trail2.getComponent<VisualComponent>()->setColor(255, 255, 255, 0);
				trail3.getComponent<VisualComponent>()->setColor(255, 255, 255, 0);
				trail4.getComponent<VisualComponent>()->setColor(255, 255, 255, 0);
				trail5.getComponent<VisualComponent>()->setColor(255, 255, 255, 0);

				score++;
				aiming = false;
			}
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

		// Logika zakonczenia poziomu
		if (AppData::getInput().isKeyPressed("P") || won) {
			if (score > 11) {
				stars = 0;
			}
			else if (score > 6) {
				stars = 1;
			}
			else if (score > 3) {
				stars = 2;
			}
			auto next = std::shared_ptr<Scene>(new ResultsScene(score, stars, 1));
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(shared_from_this(), next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
		}
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

		won = false;
		score = 0;
		scoreChanged = false;
		stars = 3;

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


		//logika poziomu:
		if (scoreChanged) {
			scoreChanged = false;
			score++;
			//mozna uzaleznic gwiazdki od dowolnych tresholdów
			if (score > 11) {
				stars = 0;
			}
			if (score > 6) {
				stars = 1;
			}
			if (score > 3) {
				stars = 2;
			}
		}

		if (AppData::getInput().isKeyPressed("P") || won) {
			auto next = std::shared_ptr<Scene>(new ResultsScene(score, stars, 2));
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(shared_from_this(), next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
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


		won = false;
		score = 0;
		scoreChanged = false;
		stars = 3;
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

		float rotateSpeed = 45.0f;  // Dostosuj prêdkoœæ obrotu wallA
		wallA.getTransform()->rot += deltaT * rotateSpeed;
		wallB.getTransform()->rot += deltaT * rotateSpeed;


		//logika poziomu:
		if (scoreChanged) {
			scoreChanged = false;
			score++;
			//mozna uzaleznic gwiazdki od dowolnych tresholdów
			if (score > 11) {
				stars = 0;
			}
			if (score > 6) {
				stars = 1;
			}
			if (score > 3) {
				stars = 2;
			}
		}

		if (AppData::getInput().isKeyPressed("P") || won) {
			auto next = std::shared_ptr<Scene>(new ResultsScene(score, stars, 3));
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(shared_from_this(), next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
		}
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

		

		won = false;
		score = 0;
		scoreChanged = false;
		stars = 3;

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

		float rotateSpeed1 = 80.0f; 
		
		wall1.getTransform()->rot -= deltaT * rotateSpeed1;
		wall2.getTransform()->rot += deltaT * rotateSpeed1;
		wall3.getTransform()->rot -= deltaT * rotateSpeed1;


		//logika poziomu:
		if (scoreChanged) {
			scoreChanged = false;
			score++;
			//mozna uzaleznic gwiazdki od dowolnych tresholdów
			if (score > 11) {
				stars = 0;
			}
			if (score > 6) {
				stars = 1;
			}
			if (score > 3) {
				stars = 2;
			}
		}

		if (AppData::getInput().isKeyPressed("P") || won) {
			auto next = std::shared_ptr<Scene>(new ResultsScene(score, stars, 4));
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(shared_from_this(), next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
		}
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


		won = false;
		score = 0;
		scoreChanged = false;
		stars = 3;

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

		//logika poziomu:
		if (scoreChanged) {
			scoreChanged = false;
			score++;
			//mozna uzaleznic gwiazdki od dowolnych tresholdów
			if (score > 11) {
				stars = 0;
			}
			if (score > 6) {
				stars = 1;
			}
			if (score > 3) {
				stars = 2;
			}
		}

		if (AppData::getInput().isKeyPressed("P") || won) {
			auto next = std::shared_ptr<Scene>(new ResultsScene(score, stars, 5));
			auto transition = std::shared_ptr<Scene>(new TransitionSceneHole(shared_from_this(), next));
			AppData::getSceneManager().pushScene(transition);
			AppData::getSceneManager().pushScene(next);
			AppData::getSceneManager().nextScene();
		}
	}

	void LevelFiveScene::render() {
		m_graphicsLayer.draw();
		guiLayer.render();
	}


}


