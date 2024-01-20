#include <pch.h>
#include "SceneManager.h"
#include "../AppData.h"
#include "dtl.h"

namespace golf {	

void SceneManager::pushScene(std::shared_ptr<Scene> newScene) {
	AppData::getInput().newScene();
	m_sceneQueueBuffer.push(newScene);
}

void SceneManager::nextScene() {
#ifndef __DIST__
	if (m_sceneQueueBuffer.empty()) {
		DTL_ERR("Attempted to switch scene when no scenes in queue are present!");
		return;
	}
#endif

	m_changeScene = true;
	m_bufferScene = m_currentScene;
	m_currentScene = m_sceneQueueBuffer.front();
	m_sceneQueueBuffer.pop();

	AppData::getInput().resetCameras();
}

void SceneManager::update(float deltaT) {
	m_currentScene->update(deltaT);
	if (m_changeScene) {
		m_bufferScene.reset();
		m_changeScene = false;
	}
}

void SceneManager::render() {
	m_currentScene->render();
}


}
