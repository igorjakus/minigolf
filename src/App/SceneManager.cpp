#include "SceneManager.h"
#include "dtl.h"

namespace golf {


SceneManager::SceneManager() = default; 

SceneManager& SceneManager::getInstance() {
	static SceneManager instance;
	return instance;
}

void SceneManager::pushScene(std::shared_ptr<Scene> newScene) {
	m_unloadedSceneQueueBuffer.push(newScene);
}

//TODO optimize for dist
void SceneManager::nextScene() {
	if(!m_loadedSceneQueueBuffer.empty()) {
		m_currentScene = m_loadedSceneQueueBuffer.front();
		m_loadedSceneQueueBuffer.pop();
	} else {
		DTL_ERR("Attempted to switch to a scene when no loaded scenes are present!");
	}
}

void SceneManager::loadNextScene() {
	if(!m_unloadedSceneQueueBuffer.empty()) {
		m_unloadedSceneQueueBuffer.front()->load();
		m_loadedSceneQueueBuffer.push(m_unloadedSceneQueueBuffer.front());
		m_unloadedSceneQueueBuffer.pop();
	} else {
		DTL_ERR("Attempted to load a scene when no scenes in queue are present!");
	}
}

void SceneManager::update(float deltaT) {
	m_currentScene->update(deltaT);
}

void SceneManager::render() {
	m_currentScene->render();
}





}
