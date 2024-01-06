#pragma once

#include "Agl.h"
#include "ECS/Component.h"
#include <vector>

namespace golf {

class TextureComponent;

class GraphicsLayer {
public:
	GraphicsLayer();

	void addObject();

	void render();

private:
	std::vector<TextureComponent> m_texturedObjects;
	agl::GraphicLayer m_layer;
	
};



class TextureComponent : public Component {
public:
	explicit TextureComponent(GraphicsLayer* graphicsLayer);
	~TextureComponent() override = default;
	TextureComponent(TextureComponent &&) = default;
	TextureComponent(const TextureComponent &) = default;
	TextureComponent &operator=(TextureComponent &&) = default;
	TextureComponent &operator=(const TextureComponent &) = default;

	void kill() override;

	void setTexture(const std::string& name);
	void resync();


private:
	agl::Object m_renderObject;
	GraphicsLayer* m_layer;

	
	friend class GraphicsLayer;
};


}
