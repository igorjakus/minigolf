#pragma once

#include "Component.h"

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

	Transform* getTransform();

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
	T* getComponent() {
		auto item = m_components.find(typeid(T));
		if(item != m_components.end()) {
			return dynamic_cast<T*>(item->second.get());
		}
		return nullptr;
	}

private:
	Transform m_transform;
	std::unordered_map<std::type_index, std::shared_ptr<Component>> m_components;
	
};


}
