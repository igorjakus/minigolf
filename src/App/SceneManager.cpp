#include "SceneManager.h"

namespace golf {


void SceneManager::pushScene(std::shared_ptr<Scene> newScene) {
	m_sceneQueueBuffer.push(newScene);
}

void SceneManager::nextScene() {
	m_currentScene = m_sceneQueueBuffer.front();
	m_sceneQueueBuffer.pop();
}

void SceneManager::loadNextScene() {
	m_sceneQueueBuffer.front()->load();
}

void SceneManager::update(float deltaT) {
	m_currentScene->update(deltaT);
}

void SceneManager::render() {
	m_currentScene->render();
}





}
