#pragma once

#include "Agl.h"
#include "ECS/Component.h"
#include "ECS/Entity.h"

namespace golf {

class VisualComponent;


class VisualComponent : public Component {
public:
	VisualComponent(agl::GraphicLayer &gl);
	~VisualComponent();

	void setOwner(Entity *entity) override;
	void setTexture(const std::string& name);
	void setAnimation(const std::string& name);
	void setColor(uchar r, uchar g, uchar b, uchar a);
	void setColor(Color color);

private:
	agl::Quad* m_quad;
};


}
