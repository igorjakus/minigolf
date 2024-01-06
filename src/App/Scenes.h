// Scenes.h 
//
// This header contains all scene class declarations

#pragma once

#include "Core/SceneManager/Scene.h"

#include <Agl.h>


namespace golf {


class BlankScene : public Scene {

public:
	BlankScene();
	~BlankScene() override = default;
	BlankScene(BlankScene &&) = delete;
	BlankScene(const BlankScene &) = delete;
	BlankScene &operator=(BlankScene &&) = delete;
	BlankScene &operator=(const BlankScene &) = delete;

	void update(float deltaT) override;
	void render() override;

private:
	agl::Camera m_camera;
	agl::GraphicLayer m_graphicsLayer;

	float timer = 0;
	std::unique_ptr<agl::Object> testObj;
	std::unique_ptr<agl::Texture> testTex;
	
};


class TestScene : public Scene {

public:
	TestScene();
	~TestScene() override = default;
	TestScene(TestScene&&) = delete;
	TestScene(const TestScene&) = delete;
	TestScene& operator=(TestScene&&) = delete;
	TestScene& operator=(const TestScene&) = delete;

	void update(float deltaT) override;
	void render() override;

private:
	agl::Camera m_camera;
	agl::GraphicLayer m_graphicsLayer;

	float speed = 0.0f;
	float size;
	float timer;
	std::unique_ptr<agl::Object> testObj;
	std::unique_ptr<agl::Animation> testTex;
	agl::Texture* temp;
	

};


class LevelOneScene : public Scene {
public:
	LevelOneScene();
	~LevelOneScene() override = default;
	LevelOneScene(LevelOneScene&&) = delete;
	LevelOneScene(const LevelOneScene&) = delete;
	LevelOneScene& operator=(LevelOneScene&&) = delete;
	LevelOneScene& operator=(const LevelOneScene&) = delete;

	void update(float deltaT) override;
	void render() override;

private:
	agl::Camera m_camera;
	agl::GraphicLayer m_graphicsLayer;

	std::unique_ptr<agl::Object> WallA;
	std::unique_ptr<agl::Object> WallB;
	std::unique_ptr<agl::Texture> WallTex;
};
}
