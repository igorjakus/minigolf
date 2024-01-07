#include "Entity.h"

namespace golf {

// Transform

Transform::Transform(float xPos, float yPos, float rotVal, float xScaleVal, float yScaleVal) //NOLINT
	:x(xPos), y(yPos), rot(rotVal), xScale(xScaleVal), yScale(yScaleVal) {}

void Transform::setPos(float xPos, float yPos) {
	x = xPos;
	y = yPos;
}
void Transform::setPos(std::pair<float, float> pos) {
	x = pos.first;
	y = pos.second;
}

std::pair<float&, float&> Transform::getPos() {
	return {x, y};
}

void Transform::setScale(float scale) {
	xScale = scale;
	yScale = scale;
}
void Transform::setScale(float xScaleVal, float yScaleVal) {
	xScale = xScaleVal;
	yScale = yScaleVal;
}
void Transform::setScale(std::pair<float, float> scale) {
	xScale = scale.first;
	yScale = scale.second;
}
std::pair<float&, float&> Transform::getScale() {
	return {xScale, yScale};
}

// Entity

Entity::Entity(float xPos, float yPos, float rot, float xScale, float yScale) //NOLINT
	:m_transform(std::make_shared<Transform>(xPos, yPos, rot, xScale, yScale)) {}

std::shared_ptr<Transform> Entity::getTransform() {
	return m_transform;
}

void Entity::removeComponent(Component& component) {
	for(auto item = m_components.begin(); item != m_components.end(); item++) {
		if(item->second.get() == &component) {
			m_components.erase(item);
			break;
		}
	}
}

void Entity::kill() {
	for(auto item : m_components) {
		item.second->kill();
	}
}

}
