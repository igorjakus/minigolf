#pragma once

#include "Scene.h"

namespace golf  {

	class SceneManager {	
	public:
		void update(float deltaT);
		void render();
	
		void pushScene(std::shared_ptr<Scene> newScene);
		void nextScene();

		void lock();
		void unlock();
		[[nodiscard]] bool isLocked() const;
	
	private:
		bool m_changeScene = false;
		bool m_lock = false;

		std::shared_ptr<Scene> m_bufferScene;
		std::shared_ptr<Scene> m_currentScene;
		std::queue<std::shared_ptr<Scene>> m_sceneQueueBuffer;	
	};

}
