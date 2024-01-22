#pragma once

#include "../Core/SceneManager/Scene.h"
#include "Agl.h"
#include "../GUI.h"
#include "../ECS/Entity.h"
#include "../physics.h"
#include "App/Background.h"
#include "App/CameraControls.h"


namespace golf {

	class LevelOneScene : public Scene {
	public:
		LevelOneScene();

		void update(float deltaT) override;
		void render() override;

	private:
		agl::Camera m_camera;
		agl::GraphicLayer m_graphicsLayer;
		GUILayer guiLayer;
		CameraControls cameraControls;
		PhysicsEngine physics;
		Background background;

		Entity grass;

		Entity wallA;
		Entity wallB;

		Entity frame1;
		Entity frame2;
		Entity frame3;
		Entity frame4;

		Entity ball;

		Entity hole;

		Entity pauseButton;
		Entity replayButton;
		Entity camLockButton;

		Entity firstDigit;
		Entity secondDigit;

		Entity starDisplay;

		bool camLocked = true;

		bool won = false;
		int score = 1;
		int stars = 3;

	};

	class LevelTwoScene : public Scene {
	public:
		LevelTwoScene();

		void update(float deltaT) override;
		void render() override;

	private:
		agl::Camera m_camera;
		agl::GraphicLayer m_graphicsLayer;
		GUILayer guiLayer;
		CameraControls cameraControls;
		PhysicsEngine physics;
		Background background;

		Entity grass;

		Entity wallA;
		Entity wallB;
		Entity frame1;
		Entity frame2;
		Entity frame3;
		Entity frame4;
		Entity spikesBlock;
		Entity wall1;
		Entity wall2;
		Entity wall3;
		Entity wall4;
		Entity wall5;

		Entity ball;

		Entity hole;

		Entity pauseButton;
		Entity replayButton;
		Entity camLockButton;

		Entity firstDigit;
		Entity secondDigit;

		Entity starDisplay;

		bool camLocked = true;

		bool won = false;
		int score = 1;
		int stars = 3;
	};

	class LevelThreeScene : public Scene {
	public:
		LevelThreeScene();

		void update(float deltaT) override;
		void render() override;

	private:
		agl::Camera m_camera;
		agl::GraphicLayer m_graphicsLayer;
		GUILayer guiLayer;
		CameraControls cameraControls;
		PhysicsEngine physics;
		Background background;

		Entity wallA;
		Entity wallB;

		Entity grass;
		Entity frame1;
		Entity frame2;
		Entity frame3;
		Entity frame4;

		Entity ball;

		Entity hole;

		Entity pauseButton;
		Entity replayButton;
		Entity camLockButton;

		Entity firstDigit;
		Entity secondDigit;

		Entity starDisplay;

		bool camLocked = true;

		bool won = false;
		int score = 1;
		int stars = 3;
	};

	class LevelFourScene : public Scene {
	public:
		LevelFourScene();

		void update(float deltaT) override;
		void render() override;

	private:
		agl::Camera m_camera;
		agl::GraphicLayer m_graphicsLayer;
		GUILayer guiLayer;
		CameraControls cameraControls;
		PhysicsEngine physics;
		Background background;

		Entity wallA;
		Entity wallB;

		Entity frame1;
		Entity frame2;
		Entity frame3;
		Entity frame4;
		Entity frame5;
		Entity frame6;

		Entity wall1;
		Entity wall2;
		Entity wall3;
		
		Entity grass;
		Entity grass2;
		Entity ramp;

		Entity ball;

		Entity hole;

		Entity pauseButton;
		Entity replayButton;
		Entity camLockButton;

		Entity firstDigit;
		Entity secondDigit;

		Entity starDisplay;

		bool camLocked = true;

		bool won = false;
		int score = 1;
		int stars = 3;
	};

	class LevelFiveScene : public Scene {
	public:
		LevelFiveScene();

		void update(float deltaT) override;
		void render() override;

	private:
		agl::Camera m_camera;
		agl::GraphicLayer m_graphicsLayer;
		GUILayer guiLayer;
		CameraControls cameraControls;
		PhysicsEngine physics;
		Background background;

		Entity grass;
		Entity wallA;
		Entity wallB;

		Entity frame1;
		Entity frame2;
		Entity frame3;
		Entity frame4;

		Entity w1;
		Entity w2;
		Entity w3;
		Entity w4;
		Entity w5;
		Entity w6;

		Entity q1;
		Entity q2;
		Entity q3;
		Entity q4;
		Entity q5;
		Entity q6;


		Entity ball;

		Entity hole;

		Entity pauseButton;
		Entity replayButton;
		Entity camLockButton;

		Entity firstDigit;
		Entity secondDigit;


		Entity starDisplay;

		bool camLocked = true;

		bool won = false;
		int score = 1;
		int stars = 3;
	};
	

	class LevelSixScene : public Scene {
	public:
		LevelSixScene();

		void update(float deltaT) override;
		void render() override;

	private:
		agl::Camera m_camera;
		agl::GraphicLayer m_graphicsLayer;
		GUILayer guiLayer;
		CameraControls cameraControls;
		PhysicsEngine physics;
		Background background;

		Entity grass;

		Entity wallA;
		Entity wallB;
		Entity wallC;

		Entity frame1;
		Entity frame2;
		Entity frame3;
		Entity frame4;

		Entity ball;

		Entity hole;

		Entity pauseButton;
		Entity replayButton;
		Entity camLockButton;

		Entity firstDigit;
		Entity secondDigit;

		Entity starDisplay;

		bool camLocked = true;

		bool won = false;
		int score = 0;
		int stars = 3;

	};
}
