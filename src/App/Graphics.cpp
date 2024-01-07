#include "Graphics.h"
#include "App/Core/AppData.h"

#include "ECS/Entity.h"
#include <memory>

namespace golf {

///////////////////
// GraphicsLayer
///////////////////

GraphicsLayer::GraphicsLayer(agl::Shader& shader, agl::Camera& camera)
	:m_aglLayer(shader, camera) {}

// To można by było zrobić jakimś templatem jeżeli będzie więcej niż jeden typ komponentu graficznego
// Ale jak jedynym komponentem graficznym będzie np VisualComponent to zmieniłbym nazwę na addComponent() np.
std::shared_ptr<TextureComponent> GraphicsLayer::addTexComponent() {
	std::shared_ptr<TextureComponent> comp = std::make_shared<TextureComponent>();
	m_texturedObjects.push_back(comp);
	m_aglLayer.addObject(comp->m_renderObject);
	return comp;
}

void GraphicsLayer::render() {
	for(auto obj : m_texturedObjects) {
		obj->resync();
	}
	m_aglLayer.draw();
}

///////////////////
// TextureComponent
///////////////////

TextureComponent::TextureComponent()
	: Component(nullptr), m_renderObject(1.f, 1.f) {}

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


}
