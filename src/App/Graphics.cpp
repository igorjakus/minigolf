#include "Graphics.h"
#include "App/Core/AppData.h"

#include "ECS/Entity.h"

namespace golf {


/// GraphicsLayer

GraphicsLayer::GraphicsLayer()
	: m_layer(AppData::getSus(), agl::Camera()){

}

void GraphicsLayer::addObject(TextureComponent* component) {
	m_texturedObjects.push_back(component);
}

void GraphicsLayer::render() {

}


/// TextureComponent

TextureComponent::TextureComponent(GraphicsLayer* graphicsLayer)
	: Component(nullptr), m_renderObject(1.f, 1.f), m_layer(graphicsLayer) {
	m_layer->addObject(this);
}

void TextureComponent::kill() {
	DTL_WAR("Usuwanie komponentów graficznych obecnie nie jest wspierane");
}

void TextureComponent::resync() {
	m_renderObject.setPosition(getTransform()->x, getTransform()->y);
	m_renderObject.setRotation(getTransform()->rot);
	m_renderObject.setScale(getTransform()->xScale, getTransform()->yScale);
}

void TextureComponent::setTexture(const std::string& name) {
	m_renderObject.setTexture(*AppData::getSus().GetTexture(name));
}

}
