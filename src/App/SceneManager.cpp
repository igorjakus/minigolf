#include "SceneManager.h"
#include "dtl.h"

namespace golf {


SceneManager::SceneManager() = default; 

SceneManager& SceneManager::getInstance() {
	static SceneManager instance;
	return instance;
}

void SceneManager::pushScene(std::shared_ptr<Scene> newScene) {
	if (m_acceptScenes) {
		m_unloadedSceneQueueBuffer.push(newScene);
	}
}

void SceneManager::nextScene() {
#ifndef __DIST__
	if (m_loadedSceneQueueBuffer.empty()) {
		DTL_ERR("Attempted to load a scene when no scenes in queue are present!");
		return;
	}
#endif

	m_requestNextScene = true;
	waitUntilNextScene();

}

void SceneManager::loadNextScene() {
	if (!m_acceptScenes) {
		return;
	}

#ifndef __DIST__
	if (m_unloadedSceneQueueBuffer.empty()) {
		DTL_ERR("Attempted to load a scene when no scenes in queue are present!");
		return;
	}
#endif

	std::shared_ptr<Scene> loadedScene = m_unloadedSceneQueueBuffer.front();
	m_loadedSceneQueueBuffer.push(loadedScene);
	m_unloadedSceneQueueBuffer.pop();

	std::thread loaderThread(&Scene::load, loadedScene.get());
	loaderThread.detach();
}

void SceneManager::waitUntilNextScene() {
#ifndef __DIST__
	if (m_loadedSceneQueueBuffer.empty()) {
		DTL_ERR("Can't wait for next scene if there are no scenes loaded in the buffer!");
	}
#endif
	m_acceptScenes = false;
}

void SceneManager::update(float deltaT) {
	if (m_requestNextScene) {
		if (m_loadedSceneQueueBuffer.front()->isLoaded()) {
			m_currentScene = m_loadedSceneQueueBuffer.front();
			m_loadedSceneQueueBuffer.pop();
			m_acceptScenes = true;
			m_requestNextScene = false;
		}
	}

	m_currentScene->update(deltaT);
}

void SceneManager::render() {
	m_currentScene->render();
}





}
