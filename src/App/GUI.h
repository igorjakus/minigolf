#pragma once

#include "ECS/Entity.h"
#include "ECS/Component.h"
#include "Agl.h"
#include <functional>

namespace golf {

class GUILayer;


// class ButtonComponent : public Component {
// public:
// 	using Callback = std::function<void>();
//
// 	void onKill() override;
// 	void onOwnerSet(Entity* entity) override;
//
// 	void setPressCallback(Callback callback);
// 	void setClickCallback(Callback callback);
// 	void setReleaseCallback(Callback callback);
// 	void setHoverCallback(Callback callback);
// 	void setHoverEnterCallback(Callback callback);
// 	void setHoverExitCallback(Callback callback);
//
// 	[[nodiscard]] bool isPressed() const;
// 	[[nodiscard]] bool isClicked() const;
// 	[[nodiscard]] bool isCursorOn() const;
//
// 	void update();
// private:
//
// 	bool m_wasPressed = false;
//
// 	Callback m_press;
// 	Callback m_click;
// 	Callback m_release;
// 	Callback m_Hover;
// 	Callback m_hoverEnter;
// 	Callback m_hoverExit;
//
// };

class GUIComponent : public Component {
public:
	explicit GUIComponent(GUILayer* layer);
	enum class positionType {
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
	enum class modeType {
		PIXEL,
		RELATIVE,
		DEFAULT
	};
	void setPosition(positionType, float offsetX, float offsetY, modeType);

	void onKill() override;
 	void onOwnerSet(Entity* entity) override;

	[[nodiscard]] float getXOffset() const;
	[[nodiscard]] float getYOffset() const;

private:
	void update(float screenWidth, float screenHeight);

	positionType m_position;
	float m_offsetX;
	float m_offsetY;
	modeType m_mode;

	GUILayer* m_layer;

	Transform* m_transform;
	bool m_owned;

	friend class GUILayer;
};


class GUILayer {
public:
	GUILayer();

	std::shared_ptr<GUIComponent> createGUIComponent();
	void deleteGUIComponent(GUIComponent* component);

	void update();
	void unconditionalUpdate();
private:
	agl::Camera m_camera;
	agl::GraphicLayer m_graphicsLayer;

	std::vector<std::shared_ptr<GUIComponent>> m_guis;
};


}
