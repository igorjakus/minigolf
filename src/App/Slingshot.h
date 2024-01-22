#pragma once

#include "ECS/Entity.h"
#include "ECS/Component.h"

#include "App/Graphics.h"

namespace golf {

class SlingshotComponent : public Component {
public:
	explicit SlingshotComponent(agl::Camera& camera, agl::GraphicLayer& graphicLayer);

	void onOwnerSet(Entity *entity) override;

	void update(float deltaT);
	[[nodiscard]] bool didShoot() const;

private:
	agl::Camera& m_camera;
	agl::GraphicLayer& m_layer;

	Entity m_button;

	float m_showBallButton = 0.f;

	Entity m_arrowTip;
	Entity m_arrowBody;
	Entity m_trail1;
	Entity m_trail2;
	Entity m_trail3;
	Entity m_trail4;
	Entity m_trail5;

	bool m_aiming = false;
	bool m_shot = false;

};




}
