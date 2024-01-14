#pragma once

#include "ECS/Component.h"
#include "ECS/Entity.h"
#include "Agl.h"
#include "App/GUI.h"

namespace golf {

class VisualComponent;


class VisualComponent : public Component {
public:
	static std::shared_ptr<VisualComponent> create(agl::GraphicLayer& graphicLayer);
	static std::shared_ptr<VisualComponent> create(agl::GraphicLayer* graphicLayer);
	static std::shared_ptr<VisualComponent> create(GUILayer& gui);
	static std::shared_ptr<VisualComponent> create(GUILayer* gui);

	explicit VisualComponent(agl::GraphicLayer* graphicLayer);
	explicit VisualComponent(GUILayer* gui);

	void onKill() override;
	void onOwnerSet(Entity* entity) override;
	void setTexture(const std::string& name);
	void setAnimation(const std::string& name);
	void setColor(uchar red, uchar green, uchar blue, uchar alpha);
	void setColor(Color color);

private:
	uint32_t m_ID;
	agl::GraphicLayer* m_GL;
};


}
