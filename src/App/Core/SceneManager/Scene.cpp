#include "Scene.h"

#include "../AppData.h"

namespace golf {



Scene::Scene()
	: m_cameraSetID(0) {
	if(!AppData::getSceneManager().isLocked()) {
		m_cameraSetID = AppData::getInput().newScene();
		DTL_INF("New scene created.");
	}
}

uint64_t Scene::getCameraSetID() const {
	return m_cameraSetID;
}



}
