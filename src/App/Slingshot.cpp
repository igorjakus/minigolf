#include "Slingshot.h"

#include "Core/AppData.h"
#include "App/GUI.h"
#include "physics.h"
#include <cassert>
#include "Util.hpp"
#include "GML/Constants.h"

namespace golf {

SlingshotComponent::SlingshotComponent(agl::Camera& camera, agl::GraphicLayer& graphicLayer)
	:m_camera(camera) , m_layer(graphicLayer) {}

void SlingshotComponent::onOwnerSet([[maybe_unused]] Entity *entity) {
	assert(getOwner()->hasComponent<DynamicPhysicsComponent>());
	m_arrowTip.addComponent<VisualComponent>(VisualComponent::create(m_layer));
	m_arrowTip.getComponent<VisualComponent>()->setTexture("arrow_tip");
	m_arrowTip.getComponent<VisualComponent>()->setColor(255, 255, 255, 0);
	m_arrowTip.getTransform()->setScale(0.5f);

	m_arrowBody.addComponent<VisualComponent>(VisualComponent::create(m_layer));
	m_arrowBody.getComponent<VisualComponent>()->setTexture("arrow_body");
	m_arrowBody.getComponent<VisualComponent>()->setColor(255, 255, 255, 0);
	m_arrowBody.getTransform()->setScale(0.4f);

	m_trail5.addComponent<VisualComponent>(VisualComponent::create(m_layer));
	m_trail5.getComponent<VisualComponent>()->setTexture("Ball");
	m_trail5.getComponent<VisualComponent>()->setColor(255, 255, 255, 0);

	m_trail4.addComponent<VisualComponent>(VisualComponent::create(m_layer));
	m_trail4.getComponent<VisualComponent>()->setTexture("Ball");
	m_trail4.getComponent<VisualComponent>()->setColor(255, 255, 255, 0);

	m_trail3.addComponent<VisualComponent>(VisualComponent::create(m_layer));
	m_trail3.getComponent<VisualComponent>()->setTexture("Ball");
	m_trail3.getComponent<VisualComponent>()->setColor(255, 255, 255, 0);

	m_trail2.addComponent<VisualComponent>(VisualComponent::create(m_layer));
	m_trail2.getComponent<VisualComponent>()->setTexture("Ball");
	m_trail2.getComponent<VisualComponent>()->setColor(255, 255, 255, 0);

	m_trail1.addComponent<VisualComponent>(VisualComponent::create(m_layer));
	m_trail1.getComponent<VisualComponent>()->setTexture("Ball");
	m_trail1.getComponent<VisualComponent>()->setColor(255, 255, 255, 0);

	m_button.addComponent<VisualComponent>(VisualComponent::create(m_layer));
	m_button.getComponent<VisualComponent>()->setTexture("BallButton");
	m_button.getComponent<VisualComponent>()->setColor(255, 255, 255, 0);
	m_button.getTransform()->setScale(0.5f);
	m_button.addComponent<ButtonComponent>(ButtonComponent::create(m_camera));

	m_trail1.getTransform()->setScale(getTransform()->xScale * 0.8f);
	m_trail2.getTransform()->setScale(m_trail1.getTransform()->xScale * 0.8f);
	m_trail3.getTransform()->setScale(m_trail2.getTransform()->xScale * 0.8f);
	m_trail4.getTransform()->setScale(m_trail3.getTransform()->xScale * 0.8f);
	m_trail5.getTransform()->setScale(m_trail4.getTransform()->xScale * 0.8f);
}

bool SlingshotComponent::didShoot() const {
	return m_shot;
}

void SlingshotComponent::update(float deltaT) {
	m_shot = false;
	if (!getOwner()->getComponent<DynamicPhysicsComponent>()->isMoving()) {
		m_button.getComponent<ButtonComponent>()->update();
		if (m_button.getComponent<ButtonComponent>()->isHovered() || m_button.getComponent<ButtonComponent>()->isPressed()) {
			m_showBallButton = 1.f;
		} else {
			m_showBallButton -= deltaT * 5.f;
		}
	} else {
		m_showBallButton = 0.f;
	}

	m_button.getTransform()->setPos(getTransform()->x, getTransform()->y);
	m_button.getComponent<VisualComponent>()->setColor(255, 255, 255, static_cast<uchar>(util::clerp(0, 255, m_showBallButton)));
	m_button.getTransform()->rot += deltaT * 90.f;

	if (m_button.getComponent<ButtonComponent>()->isPressed()) {
		m_aiming = true;
		AppData::getInput().setMousePosLock(true);
	}
	const float maxShotStrength = 2.f;
	if (m_aiming) {
		auto [x, y] = AppData::getInput().getMouseWorldOffset(m_camera);
		GML::Vec2f pos = { x, y };
		GML::Vec2f norm = pos.normalized();
		float strength = util::clamp(pos.getLength(), 0, maxShotStrength);
		GML::Vec2f val = norm * strength;

		float angle = -std::atan(x / y) * GML::F_RAD_TO_DEG;
		if (y >= 0) { angle += 180; }
		float param = util::norm(0, maxShotStrength, strength);
		uchar red = static_cast<uchar>(util::clerp(150, 230, param));
		uchar green = static_cast<uchar>(util::clerp(255, 0, param));
		m_arrowTip.getComponent<VisualComponent>()->setColor(red, green, 0, 255);
		m_arrowTip.getTransform()->rot = angle;
		m_arrowBody.getComponent<VisualComponent>()->setColor(red, green, 0, 255);
		m_arrowBody.getTransform()->rot = angle;

		m_arrowTip.getTransform()->setPos(getTransform()->x + norm.x * (m_arrowTip.getTransform()->xScale / 2 + 0.1f),
								  getTransform()->y + norm.y * (m_arrowTip.getTransform()->xScale / 2 + 0.1f));
		m_arrowBody.getTransform()->yScale = val.getLength();
		m_arrowBody.getTransform()->setPos(getTransform()->x + norm.x * (m_arrowBody.getTransform()->yScale / 2 + m_arrowTip.getTransform()->xScale + 0.11f),
								   getTransform()->y + norm.y * (m_arrowBody.getTransform()->yScale / 2 + m_arrowTip.getTransform()->xScale + 0.11f));

		m_trail1.getTransform()->setPos(getTransform()->x - 1 * val.x * 0.3f, getTransform()->y - 1 * val.y * 0.3f);
		m_trail2.getTransform()->setPos(getTransform()->x - 2 * val.x * 0.3f, getTransform()->y - 2 * val.y * 0.3f);
		m_trail3.getTransform()->setPos(getTransform()->x - 3 * val.x * 0.3f, getTransform()->y - 3 * val.y * 0.3f);
		m_trail4.getTransform()->setPos(getTransform()->x - 4 * val.x * 0.3f, getTransform()->y - 4 * val.y * 0.3f);
		m_trail5.getTransform()->setPos(getTransform()->x - 5 * val.x * 0.3f, getTransform()->y - 5 * val.y * 0.3f);

		m_trail1.getComponent<VisualComponent>()->setColor(255, 255, 255, static_cast<uchar>(255 * 0.8f));
		m_trail2.getComponent<VisualComponent>()->setColor(255, 255, 255, static_cast<uchar>(255 * 0.8f * 0.8f));
		m_trail3.getComponent<VisualComponent>()->setColor(255, 255, 255, static_cast<uchar>(255 * 0.8f * 0.8f * 0.8f));
		m_trail4.getComponent<VisualComponent>()->setColor(255, 255, 255, static_cast<uchar>(255 * 0.8f * 0.8f * 0.8f * 0.8f));
		m_trail5.getComponent<VisualComponent>()->setColor(255, 255, 255, static_cast<uchar>(255 * 0.8f * 0.8f * 0.8f * 0.8f * 0.8f));

		if (m_button.getComponent<ButtonComponent>()->isReleased()) {
			AppData::getInput().setMousePosLock(false);
			m_button.getComponent<ButtonComponent>()->update();

			getOwner()->getComponent<DynamicPhysicsComponent>()->apply_impulse({ -val.x, -val.y, 0 }, { 0, 0, 0 });

			m_arrowTip.getComponent<VisualComponent>()->setColor(255, 255, 255, 0);
			m_arrowBody.getComponent<VisualComponent>()->setColor(255, 255, 255, 0);
			m_trail1.getComponent<VisualComponent>()->setColor(255, 255, 255, 0);
			m_trail2.getComponent<VisualComponent>()->setColor(255, 255, 255, 0);
			m_trail3.getComponent<VisualComponent>()->setColor(255, 255, 255, 0);
			m_trail4.getComponent<VisualComponent>()->setColor(255, 255, 255, 0);
			m_trail5.getComponent<VisualComponent>()->setColor(255, 255, 255, 0);

			m_aiming = false;
			m_shot = true;
		}
	}

	if (getOwner()->getComponent<DynamicPhysicsComponent>()->exploded()) {
		m_button.getTransform()->setPos(getTransform()->x, getTransform()->y);
		m_button.getComponent<VisualComponent>()->setTexture("bum");
		m_button.getComponent<VisualComponent>()->setColor(255, 255, 255, 255);
		m_button.getTransform()->rot += deltaT * 720.f;
		m_button.getTransform()->setScale(m_button.getTransform()->xScale * (1 + 5 * deltaT));
	}
}



}
