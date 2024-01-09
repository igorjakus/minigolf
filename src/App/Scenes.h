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

	//Entity m_kot;
	//Entity m_kot2;

	agl::Quad* test;
	agl::Quad* test2;

	float x1, y1, sx1, sy1, r1;
	float x2, y2, sx2, sy2, r2;

	float timer = 0;
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


}

//NOLINTEND
