#pragma once

#include "Agl.h"
#include "ECS/Component.h"
#include "ECS/Entity.h"

namespace golf {

class TextureComponent;


class TextureComponent : public Component {
public:
	TextureComponent();

	void kill() override;
	void setOwner(Entity *entity) override;
	void setTexture(const std::string& name);

private:
	void resync();

	std::shared_ptr<Transform> m_transform;
};


}
