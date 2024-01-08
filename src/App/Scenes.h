// Scenes.h 
//
// This header contains all scene class declarations

#pragma once

#include "Core/SceneManager/Scene.h"
#include "ECS/Entity.h"
#include "Graphics.h"

#include <Agl.h>
#include <array>


//NOLINTBEGIN

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

	Entity m_kot;

	float timer = 0;

	agl::Quad* testObj;
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

	// Tak deklarujemy wszystkie entity. Dosłownie tyle wystarczy aby obiekt istniał w świecie.
	Entity testObj;
	static const uint spoingCount = 10;
	std::array<Entity, spoingCount> someSpoingbobs; // a tu cała lista entity
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

	agl::Quad* WallA;
	agl::Quad* WallB;
	std::unique_ptr<agl::Texture> WallTex;

	float speed = 0.0f;
	float size;
	float timer;
	agl::Quad* testObj;
	std::unique_ptr<agl::Animation> testTex;
	agl::Texture* temp;

};

}

//NOLINTEND
