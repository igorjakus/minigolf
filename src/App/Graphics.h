#pragma once

#include "Agl.h"
#include "ECS/Component.h"

namespace golf {


class TextureComponent : public Component {
public:
	explicit TextureComponent(agl::GraphicLayer* graphicsLayer);
	~TextureComponent() override = default;
	TextureComponent(TextureComponent &&) = default;
	TextureComponent(const TextureComponent &) = default;
	TextureComponent &operator=(TextureComponent &&) = default;
	TextureComponent &operator=(const TextureComponent &) = default;

	void kill() override;

	void resync();
	void setTexture(const std::string& name);


private:
	agl::Object m_renderObject;
	agl::GraphicLayer* m_layer;

	agl::Object& getAglObj();
};


}
