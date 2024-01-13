#pragma once

#include "ECS/Entity.h"
#include "ECS/Component.h"
#include "Agl.h"
#include <functional>
#include <list>

namespace golf {

class GUIComponent : public Component {
public:
	using Callback = std::function<void>();

	void onKill() override;
	void onOwnerSet(Entity* entity) override;

	void setPressCallback(Callback callback);
	void setClickCallback(Callback callback);
	void setReleaseCallback(Callback callback);
	void setHoverCallback(Callback callback);
	void setHoverEnterCallback(Callback callback);
	void setHoverExitCallback(Callback callback);

	[[nodiscard]] bool isPressed() const;
	[[nodiscard]] bool isClicked() const;
	[[nodiscard]] bool isCursorOn() const;

	enum class position {
		TOP,
		BOTTOM,
		LEFT,
		RIGHT,
		CENTER,
		TOPLEFT,
		TOPRIGHT,
		BOTTOMLEFT,
		BOTTOMRIGHT,
		DEFAULT
	};
	enum class mode {
		PIXEL,
		RELATIVE,
		DEFAULT
	};
	void setPosition(position, float offsetX, float offsetY, mode);

private:
	explicit GUIComponent();
	void update();

	bool m_wasPressed = false;

	Callback m_press;
	Callback m_click;
	Callback m_release;
	Callback m_Hover;
	Callback m_hoverEnter;
	Callback m_hoverExit;

	position m_position;
	float m_offsetX;
	float m_offsetY;
	mode m_mode;

	friend class GUILayer;
};


class GUILayer {
public:
	GUILayer();

	std::shared_ptr<GUIComponent> createGUIComponent();

	void update(float deltaT);
	void render();
private:
	agl::Camera m_camera;
	agl::GraphicLayer m_graphicsLayer;

	std::list<GUIComponent> m_guis;
};





}
