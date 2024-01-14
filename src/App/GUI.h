#pragma once

#include "ECS/Entity.h"
#include "ECS/Component.h"
#include "Agl.h"

namespace golf {

class GUILayer;

class ButtonComponent : public Component {
public:
	static std::shared_ptr<ButtonComponent> create(agl::Camera&);
	static std::shared_ptr<ButtonComponent> create(agl::Camera*);
	static std::shared_ptr<ButtonComponent> create(GUILayer&);
	static std::shared_ptr<ButtonComponent> create(GUILayer*);

	explicit ButtonComponent(agl::Camera& camera);
	explicit ButtonComponent(GUILayer& gui);

	[[nodiscard]] bool isPressed() const;
	[[nodiscard]] bool isClicked() const;
	[[nodiscard]] bool isReleased() const;
	[[nodiscard]] bool isHovered() const;
	[[nodiscard]] bool isEnteringHover() const;
	[[nodiscard]] bool isExitingHover() const;

	void update();

private:
	agl::Camera* m_camera;

	bool m_pressed = false;
	bool m_wasPressed = false;
	bool m_hovered = false;
	bool m_wasHovered = false;
};

class GUIComponent : public Component {
public:
	static std::shared_ptr<GUIComponent> create(GUILayer*);
	static std::shared_ptr<GUIComponent> create(GUILayer&);

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

	void render();
	void unconditionalUpdate();

	agl::Camera* getCamera();
	agl::GraphicLayer* getLayer();
private:
	agl::Camera m_camera;
	agl::GraphicLayer m_graphicsLayer;

	std::vector<std::shared_ptr<GUIComponent>> m_guis;
};


}
