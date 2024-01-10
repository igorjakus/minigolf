#pragma once
#include "Scene.h"

namespace golf 
{
	class SceneManager {	
	public:
		void update(float deltaT);
		void render();
	
		void pushScene(std::shared_ptr<Scene> newScene);
		void nextScene();
	
	private:
		std::shared_ptr<Scene> m_currentScene;
		std::queue<std::shared_ptr<Scene>> m_sceneQueueBuffer;	
	};
}
