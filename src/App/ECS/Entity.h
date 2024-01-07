#pragma once

#include "Component.h"
#include "dtl.h"

#include <memory>
#include <type_traits>
#include <typeindex>
#include <unordered_map>

namespace golf {

struct Transform {
	explicit Transform(float xPos = 0.f, float yPos = 0.f, float rot = 0.f, float xScale = 1.f, float yScale = 1.f);

	float x, y, rot, xScale, yScale;

	void setPos(float xPos, float yPos);
	void setPos(std::pair<float, float> pos);
	std::pair<float&, float&> getPos();

	void setScale(float scale);
	void setScale(float xScaleVal, float yScaleVal);
	void setScale(std::pair<float, float> scale);
	std::pair<float&, float&> getScale();
};

class Entity {
public:
	explicit Entity(float xPos = 0.f, float yPos = 0.f, float rot = 0.f, float xScale = 1.f, float yScale = 1.f);
	explicit Entity(float xPos, float yPos, float rot);
	explicit Entity(float xPos, float yPos);

	std::shared_ptr<Transform> getTransform();

	void kill();

	template <typename T>
	void addComponent(std::shared_ptr<T> component) {
		addComponent<T, true>(component);
	}

	template <typename T, std::enable_if_t<std::is_base_of_v<Component, T>, bool>>
	void addComponent(std::shared_ptr<T> component) {
		auto item = m_components.find(typeid(T));
		if(item != m_components.end()) {
			item->second->releaseFromOwner();
		}
		component->setOwner(this);
		m_components.emplace(typeid(T), component);
	}

	template <typename T>
	[[nodiscard]] std::shared_ptr<T> getComponent() {
		auto item = m_components.find(typeid(T));
		if(item != m_components.end()) {
			return std::dynamic_pointer_cast<T>(item->second);
		}
		return nullptr;
	}


	template <typename T>
	bool hasComponent() {
		return m_components.find(typeid(T)) != m_components.end(); 
	}

	template <typename T>
	bool removeComponent() {
		auto item = m_components.find(typeid(T));
		bool found = item != m_components.end();
		if(found) {
			item->second->kill();
		}
		return found;
	}

	void removeComponent(Component& component);

private:
	std::shared_ptr<Transform> m_transform;
	std::unordered_map<std::type_index, std::shared_ptr<Component>> m_components;
	
};


}
