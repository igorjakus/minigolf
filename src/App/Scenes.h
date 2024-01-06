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
	//std::unique_ptr<agl::Texture> testTex;
	agl::Texture* temp;
	

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

	std::unique_ptr<agl::Object> WallA;
	std::unique_ptr<agl::Object> WallB;
	std::unique_ptr<agl::Texture> WallTex;
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
