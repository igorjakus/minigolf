#include <pch.h>
#include "SceneManager.h"
#include "../AppData.h"
#include "dtl.h"

namespace golf {	

void SceneManager::pushScene(std::shared_ptr<Scene> newScene) {
	if (m_lock) {
		DTL_WAR("Attempted so push a scene in Scene Manager locked state!");
		return;
	}
	m_sceneQueueBuffer.push(newScene);
}

void SceneManager::nextScene() {
#ifndef __DIST__
	if (m_sceneQueueBuffer.empty()) {
		DTL_ERR("Attempted to switch scene when no scenes in queue are present!");
		return;
	}
#endif

	if (m_lock) {
		DTL_WAR("Attempted so switch scene in Scene Manager locked state!");
		return;
	}

	m_changeScene = true;
	m_bufferScene = m_currentScene;
	m_currentScene = m_sceneQueueBuffer.front();
	m_sceneQueueBuffer.pop();

	AppData::getInput().changeCameraSet(m_currentScene);
}

void SceneManager::lock() {
	m_lock = true;
}

void SceneManager::unlock() {
	m_lock = false;
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
