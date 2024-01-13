#include "pch.h"
#include "GUI.h"
#include "App/Core/AppData.h"

namespace golf {


GUIComponent::GUIComponent(GUILayer* layer)
	: m_position(positionType::CENTER), m_offsetX(0), m_offsetY(0), m_mode(modeType::RELATIVE), m_layer(layer), m_transform(nullptr), m_owned(false) {}

void GUIComponent::setPosition(positionType position, float offsetX, float offsetY, modeType mode) {
	if(position != positionType::DEFAULT) {
		m_position = position;
	}
	if(mode != modeType::DEFAULT) {
		m_mode = mode;
	}

	m_offsetX = offsetX;
	m_offsetY = offsetY;

}

void GUIComponent::onKill() {
	m_layer->deleteGUIComponent(this);
}

void GUIComponent::onOwnerSet(Entity* entity) {
	m_transform = entity->getTransform();
	m_owned = true;
}

void GUIComponent::update(float screenWidth, float screenHeight) { //NOLINT
	if(m_owned) [[likely]] {
		auto[x, y] = m_transform->getPos();
		auto[xScale, yScale] = m_transform->getScale();
		float rot = m_transform->rot;

		const float TO_DEG = 180.f / static_cast<float>(M_PI);
		const float effWidth = (xScale * cosf(rot * TO_DEG) + yScale * sinf(rot * TO_DEG)) / 2;
		const float effHeight = (yScale * cosf(rot * TO_DEG) + xScale * sinf(rot * TO_DEG)) / 2;

		switch (m_position) {
			case positionType::CENTER:
				x = 0;
				y = 0;
				break;
			case positionType::TOP:
				x = 0;
				y = screenHeight / 2 - effHeight;
				break;
			case positionType::BOTTOM:
				x = 0;
				y = -screenHeight / 2 + effHeight;
				break;
			case positionType::LEFT:
				x = -screenWidth / 2 + effWidth;
				y = 0;
				break;
			case positionType::RIGHT:
				x = screenWidth / 2 - effWidth;
				y = 0;
				break;
			case positionType::TOPLEFT:
				x = -screenWidth / 2 + effWidth;
				y = screenHeight / 2 - effHeight;
				break;
			case positionType::TOPRIGHT:
				x = screenWidth / 2 - effWidth;
				y = screenHeight / 2 - effHeight;
				break;
			case positionType::BOTTOMLEFT:
				x = -screenWidth / 2 + effWidth;
				y = -screenHeight / 2 + effHeight;
				break;
			case positionType::BOTTOMRIGHT:
				x = screenWidth / 2 - effWidth;
				y = -screenHeight / 2 + effHeight;
				break;
			default:
				break;
		}

		const float xOffset = (m_mode == modeType::RELATIVE) ? m_offsetX : (m_offsetX / static_cast<float>(AppData::getWindow().getWindowSize().y));
		const float yOffset = (m_mode == modeType::RELATIVE) ? m_offsetY : (m_offsetY / static_cast<float>(AppData::getWindow().getWindowSize().y));

		x += xOffset;
		y += yOffset;
	}
}

float GUIComponent::getXOffset() const {
	return m_offsetX;
}

float GUIComponent::getYOffset() const {
	return m_offsetY;
}

///////////////////////////////////////////
/// GUI layer
///////////////////////////////////////////

GUILayer::GUILayer()
	:m_camera(0, 0, 1.f, 1.f, 1.f), m_graphicsLayer(*AppData::getSus().GetShader("DefaultShader.glsl"), m_camera) {

	AppData::getInput().attachCamera(&m_camera, 1.f, true);
}

std::shared_ptr<GUIComponent> GUILayer::createGUIComponent() {
	std::shared_ptr<GUIComponent> comp = std::make_shared<GUIComponent>(this);
	m_guis.push_back(comp);

	return comp;
}

void GUILayer::deleteGUIComponent(GUIComponent* component) {
	auto iterator = std::find_if(m_guis.begin(), m_guis.end(), [component](const auto& ptr){
		return ptr.get() == component;
	});
	if(iterator != m_guis.end()) {
		m_guis.erase(iterator);
	}
}

void GUILayer::update() {
	const float width = m_camera.getSize().x;
	const float height = m_camera.getSize().y;
	for(auto& comp : m_guis) {
		comp->update(width, height);
	}
}


}
