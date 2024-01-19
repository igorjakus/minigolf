#include "Scene.h"

#include "../AppData.h"

namespace golf {

	Scene::Scene() {
		DTL_INF("New scene created.");

		AppData::getInput().newScene();
	}

}