#include "pch.h"
#include "Agl.h"
#include "GUI.h"
#include "App/Core/AppData.h"

namespace golf {

/////////////////////////////////
/// Button component
/////////////////////////////////

std::shared_ptr<ButtonComponent> ButtonComponent::create(agl::Camera& camera) {
	return std::make_shared<ButtonComponent>(camera);
}
std::shared_ptr<ButtonComponent> ButtonComponent::create(agl::Camera* camera) {
	return std::make_shared<ButtonComponent>(*camera);
}
std::shared_ptr<ButtonComponent> ButtonComponent::create(GUILayer& gui) {
	return std::make_shared<ButtonComponent>(gui);
}
std::shared_ptr<ButtonComponent> ButtonComponent::create(GUILayer* gui) {
	return std::make_shared<ButtonComponent>(*gui);
}

ButtonComponent::ButtonComponent(agl::Camera& camera)
	:m_camera(&camera) {}

ButtonComponent::ButtonComponent(GUILayer& gui)
	:m_camera(gui.getCamera()) {}

bool ButtonComponent::isPressed() const {
	return m_pressed;
}

bool ButtonComponent::isClicked() const {
	return m_pressed && !m_wasPressed;
}

bool ButtonComponent::isReleased() const {
	return !m_pressed && m_wasPressed;
}

bool ButtonComponent::isHovered() const {
	return m_hovered;
}

bool ButtonComponent::isEnteringHover() const {
	return m_hovered && !m_wasHovered;
}

bool ButtonComponent::isExitingHover() const {
	return !m_hovered && m_wasHovered;
}

void ButtonComponent::update() {
	m_wasHovered = m_hovered;
	m_wasPressed = m_pressed;
	auto[x, y] = AppData::getInput().getMouseWorldPos(*m_camera);
	float xPos = getTransform()->x;
	float yPos = getTransform()->y;
	float rot = getTransform()->rot;
	float xScale = getTransform()->xScale;
	float yScale = getTransform()->yScale;
	if(rot == 0) [[likely]] {
		m_hovered =  x > xPos - xScale / 2 && x < xPos + xScale / 2 && y > yPos - yScale / 2 && y < yPos + yScale / 2;
	} else [[unlikely]] {
		DTL_WAR("Obrócone przyciski obecnie nie działają");
		m_hovered = false;
	}

	if(!AppData::getInput().isLeftMousePressed()) {
		m_pressed = false;
	}
	if(m_hovered && AppData::getInput().isLeftMouseClicked()) {
		m_pressed = true;
	}
}

/////////////////////////////////
/// GUI component
/////////////////////////////////

std::shared_ptr<GUIComponent> GUIComponent::create(GUILayer* gui) {
	return gui->createGUIComponent();
}
std::shared_ptr<GUIComponent> GUIComponent::create(GUILayer& gui) {
	return gui.createGUIComponent();
}

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

		const float TO_DEG = 180.f / static_cast<float>(PI);
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

		const uint windowX = AppData::getWindow().getWindowSize().x;
		const uint windowY = AppData::getWindow().getWindowSize().y;
		const auto max = static_cast<float>(windowX > windowY ? windowX : windowY);

		x += (m_mode == modeType::RELATIVE) ? m_offsetX : (m_offsetX / max);
		y += (m_mode == modeType::RELATIVE) ? m_offsetY : (m_offsetY / max);
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

void GUILayer::render() {
	const float width = m_camera.getSize().x;
	const float height = m_camera.getSize().y;
	for(auto& comp : m_guis) {
		comp->update(width, height);
	}
	m_graphicsLayer.draw();
}

agl::Camera* GUILayer::getCamera() {
	return &m_camera;
}

agl::GraphicLayer* GUILayer::getLayer() {
	return &m_graphicsLayer;
}


}
