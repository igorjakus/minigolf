#pragma once

#include "../Core/SceneManager/Scene.h"
#include "../GUI.h"
#include "../ECS/Entity.h"


namespace golf {

	class TransitionSceneHole : public Scene {
	public:
		explicit TransitionSceneHole(std::shared_ptr<Scene> current, std::shared_ptr<Scene> next);

		void update(float deltaT) override;
		void render() override;

	private:
		GUILayer m_layer;

		Entity m_plane;

		float m_duration;
		float m_pause;
		float m_time = 0;

		std::shared_ptr<Scene> m_scene1;
		std::shared_ptr<Scene> m_scene2;
	};

	
	class TransitionSceneFade : public Scene {
	public:
		explicit TransitionSceneFade(std::shared_ptr<Scene> current, std::shared_ptr<Scene> next);

		void update(float deltaT) override;
		void render() override;

	private:
		GUILayer m_layer;

		Entity m_plane;

		float m_duration;
		float m_pause;
		float m_time = 0;

		std::shared_ptr<Scene> m_scene1;
		std::shared_ptr<Scene> m_scene2;
	};

}
