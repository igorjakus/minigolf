#include "Graphics.h"
#include "App/Core/AppData.h"
#include "dtl.h"

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
		if(obj->m_transform) [[likely]] { // if do usunięcia jak będzie pożądnie napisane TextureComponent::kill();
			obj->resync();
		}
	}
	m_aglLayer.draw();
}

///////////////////
// TextureComponent
///////////////////

TextureComponent::TextureComponent()
	: Component(nullptr), m_renderObject(1.f, 1.f) {}

void TextureComponent::kill() {
	Component::kill();
	m_transform.reset();
	const float WCHUJDALEKO = 999999.0f;
	m_renderObject.setPosition(WCHUJDALEKO, WCHUJDALEKO); // Tu pewnie należałoby usuwać m_renderObject z agl::GraphicLayer ale idk jak
	// bo w tym momencie on dalej jest renderowany i to niepotrzebnie
	DTL_INF("Killed graphics component");
}

void TextureComponent::setOwner(Entity *entity) {
	Component::setOwner(entity);
	m_transform = getTransform();
}

void TextureComponent::setTexture(const std::string& name) {
	m_renderObject.setTexture(*AppData::getSus().GetTexture(name));
}

void TextureComponent::resync() {
	if(!m_transform) [[unlikely]] {
		DTL_WAR("Próba zsynchronizowania komponentu graficznego z Transformem, gdy komponent nie ma przypisanego transforma! (sprawdź czy obiekt ma poprawnie przypisanego właściciela)");
		return;
	}
	m_renderObject.setPosition(m_transform->x, m_transform->y);
	m_renderObject.setRotation(m_transform->rot);
	m_renderObject.setScale(m_transform->xScale, m_transform->yScale);
}


}
