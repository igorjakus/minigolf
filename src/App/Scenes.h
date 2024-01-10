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

class LevelSelectionScene : public Scene {
public:
	LevelSelectionScene();
	~LevelSelectionScene() override = default;
	LevelSelectionScene(LevelSelectionScene&&) = delete;
	LevelSelectionScene(const LevelSelectionScene&) = delete;
	LevelSelectionScene& operator=(LevelSelectionScene&&) = delete;
	LevelSelectionScene& operator=(const LevelSelectionScene&) = delete;

	void update(float deltaT) override;
	void render() override;

private:
	agl::Camera m_camera;
	agl::GraphicLayer m_graphicsLayer;

	std::unique_ptr<agl::Object> cokolwiek;
	bool isFirstUpdate = true;

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

	Entity wallA;
	Entity wallB;
	bool isFirstUpdate = true;
};

void startLevel(int levelNumber);

class ResultsScene : public Scene {
public:
	ResultsScene(int score, int lvlNumber);
	~ResultsScene() override = default;
	ResultsScene(ResultsScene&&) = delete;
	ResultsScene(const ResultsScene&) = delete;
	ResultsScene& operator=(ResultsScene&&) = delete;
	ResultsScene& operator=(const ResultsScene&) = delete;

	void update(float deltaT) override;
	void render() override;

private:
	agl::Camera m_camera;
	agl::GraphicLayer m_graphicsLayer;
	int playerScore;
	bool isFirstUpdate = true;
	int finishedLevelNumber;
};

class LevelTwoScene : public Scene {
public:
	LevelTwoScene();
	~LevelTwoScene() override = default;
	LevelTwoScene(LevelTwoScene&&) = delete;
	LevelTwoScene(const LevelTwoScene&) = delete;
	LevelTwoScene& operator=(LevelTwoScene&&) = delete;
	LevelTwoScene& operator=(const LevelTwoScene&) = delete;

	void update(float deltaT) override;
	void render() override;

private:
	agl::Camera m_camera;
	agl::GraphicLayer m_graphicsLayer;

	std::unique_ptr<agl::Object> WallA;
	std::unique_ptr<agl::Object> WallB;
	std::unique_ptr<agl::Texture> WallTex;
	bool isFirstUpdate = true;
};

}

//NOLINTEND
