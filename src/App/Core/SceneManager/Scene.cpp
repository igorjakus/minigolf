#include "Scene.h"

#include "../AppData.h"

namespace golf {

	Scene::Scene()
		: m_cameraSetID(0) {
		DTL_INF("New scene created.");

		m_cameraSetID = AppData::getInput().newScene();
	}

	uint64_t Scene::getCameraSetID() {
		return m_cameraSetID;
	}

}
