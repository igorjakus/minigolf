#include "pch.h"
#include "transition.h"
#include "../Graphics.h"
#include "../Core/AppData.h"
#include "Util.hpp"

namespace golf {


	TransitionSceneHole::TransitionSceneHole(std::shared_ptr<Scene> current, std::shared_ptr<Scene> next)
		:m_layer("HoleTransition.glsl"), m_duration(1.0f), m_pause(0.05f),
		 m_scene1(std::move(current)), m_scene2(std::move(next)) {

		m_plane.addComponent<GUIComponent>(m_layer.createGUIComponent());
		m_plane.addComponent<VisualComponent>(VisualComponent::create(m_layer));

		if (!m_scene2) {
			DTL_ERR("Przejscie miedzy scenami nie ma drugiej sceny!");
		}
	}

	void TransitionSceneHole::update([[maybe_unused]] float deltaT) {
		m_time += deltaT;
		AppData::getSceneManager().lock();

		if (m_time > m_duration / 2 + m_pause / 2) {
			m_scene2->update(deltaT);
		}

		if (m_time > m_duration) {
			AppData::getSceneManager().unlock();
			AppData::getSceneManager().nextScene();
		}
	}

	void TransitionSceneHole::render() {
		uint8_t radius = 0;
		if (m_time <= m_duration / 2 - m_pause / 2) {
			m_scene1->render();

			float param = util::cnorm(0, m_duration / 2 - m_pause / 2, m_time);
			radius = static_cast<uint8_t>(util::clerp(255, 0, -(1-param)*(1-param)*(1-param)*(1-param) + 1));
		} else if (m_time > m_duration / 2 + m_pause / 2) {
			m_scene2->render();

			float param = util::cnorm(m_duration / 2 + m_pause / 2, m_duration, m_time);
			radius = static_cast<uint8_t>(util::clerp(0, 255, param*param*param*param));
		}
		m_plane.getComponent<VisualComponent>()->setColor(radius, 0, 0, 0);
		m_layer.render();
	}
}
