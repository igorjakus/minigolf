#pragma once

#include "../Core/SceneManager/Scene.h"
#include "Agl.h"
#include "../GUI.h"
#include "../ECS/Entity.h"


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

		Entity grass;

		Entity wallA;
		Entity wallB;

		Entity frame1;
		Entity frame2;
		Entity frame3;
		Entity frame4;
		Entity pauseButton;
		bool won;
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
	};
}