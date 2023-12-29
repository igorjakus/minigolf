// Scenes.h 
//
// This header contains all scene class declarations

#pragma once

#include "Agl.h"
#include "Scene.h"

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

	// TEMP
	int timer = 0;
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

	float speed = 0.001;
	float pos = 0;
	std::unique_ptr<agl::Object> testObj;
	std::unique_ptr<agl::Texture> testTex;

};


}
