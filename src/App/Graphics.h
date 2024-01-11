#pragma once

#include "Agl.h"
#include "ECS/Component.h"
#include "ECS/Entity.h"

namespace golf {

class VisualComponent;


class VisualComponent : public Component {
public:
	explicit VisualComponent(agl::GraphicLayer* graphicLayer);

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
