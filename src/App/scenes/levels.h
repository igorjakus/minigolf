#pragma once

#include "../Core/SceneManager/Scene.h"
#include "Agl.h"
#include "../GUI.h"
#include "../ECS/Entity.h"
#include "../physics.h"


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

		PhysicsEngine physics;

		Entity grass;

		Entity wallA;
		Entity wallB;

		Entity frame1;
		Entity frame2;
		Entity frame3;
		Entity frame4;

		float showBallButton = 0.f;
		Entity ballButton;
		Entity ball;

		Entity hole;

		Entity arrowTip;
		Entity arrowBody;
		Entity trail1;
		Entity trail2;
		Entity trail3;
		Entity trail4;
		Entity trail5;

		float camUpSpeed = 0;
		float camDownSpeed = 0;
		float camRightSpeed = 0;
		float camLeftSpeed = 0;
		Entity camLeft;
		Entity camRight;
		Entity camUp;
		Entity camDown;
		float camMinX = 0.f;
		float camMaxX = 8.f;
		float camMinY = 0.f;
		float camMaxY = 6.f;
		float zoom = 1.f;
		float targetZoom = 0.5f;
		float zoomTimer = 1.f;

		bool camLocked = true;

		Entity pauseButton;
		Entity replayButton;
		Entity camLockButton;

		Entity firstDigit;
		Entity secondDigit;

		bool aiming = false;


		bool won = false;
		int score = 0;
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

		std::unique_ptr<agl::Object> WallA;
		std::unique_ptr<agl::Object> WallB;
		std::unique_ptr<agl::Texture> WallTex;
		Entity wallA;
		Entity wallB;

		Entity frame1;
		Entity frame2;
		Entity frame3;
		Entity frame4;
		Entity pauseButton;

		bool won;
		int score;
		bool scoreChanged;
		int stars;
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

		Entity wallA;
		Entity wallB;

		Entity frame1;
		Entity frame2;
		Entity frame3;
		Entity frame4;
		Entity pauseButton;

		bool won;
		int score;
		bool scoreChanged;
		int stars;
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
		Entity wall4;
		Entity pauseButton;

		bool won;
		int score;
		bool scoreChanged;
		int stars;
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

		Entity wallA;
		Entity wallB;

		Entity frame1;
		Entity frame2;
		Entity frame3;
		Entity frame4;
		Entity pauseButton;

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

		bool won;
		int score;
		bool scoreChanged;
		int stars;
	};
	
	
}