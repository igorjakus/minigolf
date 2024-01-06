#include "Graphics.h"
#include "App/Core/AppData.h"

#include "ECS/Entity.h"

namespace golf {

TextureComponent::TextureComponent(agl::GraphicLayer* graphicsLayer)
	: Component(nullptr), m_renderObject(1.f, 1.f), m_layer(graphicsLayer) {
	m_layer->addObject(m_renderObject);
}

void TextureComponent::kill() {
	DTL_WAR("Usuwanie komponentów graficznych obecnie nie jest wspierane");
}

void TextureComponent::setTexture(const std::string& name) {
	m_renderObject.setTexture(*AppData::getSus().GetTexture(name));
}

void TextureComponent::resync() {
	m_renderObject.setPosition(getTransform()->x, getTransform()->y);
	m_renderObject.setRotation(getTransform()->rot);
	m_renderObject.setScale(getTransform()->xScale, getTransform()->yScale);
}

agl::Object& TextureComponent::getAglObj() {
	return m_renderObject;
}


}
