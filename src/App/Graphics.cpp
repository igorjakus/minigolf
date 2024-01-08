#include "Graphics.h"
#include "App/Core/AppData.h"
#include "dtl.h"

#include <memory>

namespace golf {

///////////////////
// TextureComponent
///////////////////

TextureComponent::TextureComponent()
	: Component(nullptr) {}

void TextureComponent::kill() {
	Component::kill();
	m_transform.reset();
	// bo w tym momencie on dalej jest renderowany i to niepotrzebnie
	DTL_INF("Killed graphics component");
}

void TextureComponent::setOwner(Entity *entity) {
	Component::setOwner(entity);
	m_transform = getTransform();
}

void TextureComponent::setTexture([[maybe_unused]] const std::string& name) {}

void TextureComponent::resync() {
	if(!m_transform) [[unlikely]] {
		DTL_WAR("Próba zsynchronizowania komponentu graficznego z Transformem, gdy komponent nie ma przypisanego transforma! (sprawdź czy obiekt ma poprawnie przypisanego właściciela)");
		return;
	}
}


}
