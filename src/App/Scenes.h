#pragma once

#include "Core/SceneManager/Scene.h"
#include "Agl.h"
#include "GUI.h"
#include "ECS/Entity.h"


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
	GUILayer m_gui;

	Entity m_kot;
	Entity m_button;
	Entity m_button2;
	Entity m_button3;

	float xS = .5f, yS = .5f;

	float timer = 0;
};

// Przykładowy "skrypt"
class BouncyComponent : public Component {
public:
	void setVelocity(std::pair<float, float> vel);
	void setBoundaries(float min1, float max1, float min2, float max2);
	void updatePosition(float deltaT);

private:
	std::pair<float, float> velocity;
	float minX, maxX, minY, maxY;
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
	
	std::array<BouncyComponent, spoingCount> comps;
};



}

//NOLINTEND
