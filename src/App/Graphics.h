#pragma once

#include "Agl.h"
#include "ECS/Component.h"

namespace golf {


class TextureComponent : Component {
public:
	explicit TextureComponent(agl::GraphicLayer* graphicLayer);
	~TextureComponent() override;
	TextureComponent(TextureComponent &&) = default;
	TextureComponent(const TextureComponent &) = default;
	TextureComponent &operator=(TextureComponent &&) = default;
	TextureComponent &operator=(const TextureComponent &) = default;

	void kill() override;

	void setTexture(const std::string& name);

private:
	agl::Object m_renderObject;
	agl::GraphicLayer* m_rederer;
	
};


}
