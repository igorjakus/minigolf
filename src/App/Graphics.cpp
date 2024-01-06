#include "Graphics.h"
#include "App/Core/AppData.h"

namespace golf {


TextureComponent::TextureComponent(agl::GraphicLayer* graphicLayer)
	: Component(nullptr), m_renderObject(1.f, 1.f), m_rederer(graphicLayer) {
	m_rederer->addObject(m_renderObject);
}

TextureComponent::~TextureComponent() = default;

void TextureComponent::kill() {

}

void TextureComponent::setTexture(const std::string& name) {
	m_renderObject.setTexture(*AppData::getSus().GetTexture(name));
}

}
