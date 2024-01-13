#pragma once

#include "ECS/Entity.h"
#include "ECS/Component.h"
#include "Agl.h"
#include <functional>

namespace golf {

class GUILayer;

class ButtonComponent : public Component {
public:
	explicit ButtonComponent(agl::Camera& camera);
	explicit ButtonComponent(GUILayer& gui);

	using Callback = std::function<void()>;

	void setPressCallback(Callback callback);
	void setClickCallback(Callback callback);
	void setReleaseCallback(Callback callback);
	void setHoverCallback(Callback callback);
	void setHoverEnterCallback(Callback callback);
	void setHoverExitCallback(Callback callback);

	[[nodiscard]] bool isPressed() const;
	[[nodiscard]] bool isClicked() const;
	[[nodiscard]] bool isCursorOn() const;

	void update();

private:
	int lol = 69;
	agl::Camera* m_camera;

	bool m_pressed = false;

	float m_xPos = 0;
	float m_yPos = 0;
	float m_rot = 0;
	float m_xScale = 1;
	float m_yScale = 1;

	Callback m_press = nullptr;
	Callback m_click = nullptr;
	Callback m_release = nullptr;
	Callback m_hover = nullptr;
	Callback m_hoverEnter = nullptr;
	Callback m_hoverExit = nullptr;
};

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

	agl::Camera* getCamera();
private:
	agl::Camera m_camera;
	agl::GraphicLayer m_graphicsLayer;

	std::vector<std::shared_ptr<GUIComponent>> m_guis;
};


}
