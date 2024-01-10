#include "SceneManager.h"

#include <dtl.h>

namespace golf {


void SceneManager::pushScene(std::shared_ptr<Scene> newScene) {
	m_sceneQueueBuffer.push(newScene);
}

void SceneManager::nextScene() {
#ifndef __DIST__
	if (m_sceneQueueBuffer.empty()) {
		DTL_ERR("Attempted to switch scene when no scenes in queue are present!");
		return;
	}
#endif

	m_currentScene.reset();
	m_currentScene = m_sceneQueueBuffer.front();
	m_sceneQueueBuffer.pop();

}

void SceneManager::update(float deltaT) {
	m_currentScene->update(deltaT);
}

void SceneManager::render() {
	m_currentScene->render();
}


}
