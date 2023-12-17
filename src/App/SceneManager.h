// SceneManager.h 
//
// A class serving as state machine for the main application.
// It stores(?) current scene and is responsible for updating
// and rendering it, as well as changing the scene.

#pragma once

#include "Scene.h"
#include <memory>
#include <queue>

namespace golf {

class SceneManager {

public:
	SceneManager () = default;
	~SceneManager () = default;
	SceneManager (SceneManager  &&) = delete;
	SceneManager (const SceneManager  &) = delete;
	SceneManager  &operator=(SceneManager  &&) = default;
	SceneManager  &operator=(const SceneManager  &) = delete;

	// void handleInput(someKindOfInputClass);
	void update(float deltaT);
	void render();

	void pushScene(std::shared_ptr<Scene> newScene);
	void nextScene();
	void loadNextScene();

private:

	std::shared_ptr<Scene> m_currentScene;
	std::queue<std::shared_ptr<Scene>> m_sceneQueueBuffer;

	
};



}
