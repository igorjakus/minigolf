#include <pch.h>
#include "Component.h"
#include "Entity.h"

#include "dtl.h"

namespace golf {


Component::Component(Entity* entity)
	:m_owner(entity) {
	
	if (m_owner != nullptr) {
		kill();
	}
}

void Component::kill() {
	onKill();
	if(m_owner != nullptr) {
		m_owner->removeComponent(this);
		m_owner = nullptr;
	}
}

void Component::setOwner(Entity* entity) {
	m_owner = entity;
	onOwnerSet(entity);
}

Entity* Component::getOwner() {
	return m_owner;
}

Transform* Component::getTransform() {
	if (m_owner == nullptr) [[unlikely]] {
#ifndef __DIST__
		DTL_ERR("Komponent sprawdza wartosc transform, gdy nie ma wlasciciela!");
#endif // !__DIST__
		return nullptr;
	}

	return m_owner->getTransform();
}

void Component::onKill() {}
void Component::onOwnerSet([[maybe_unused]] Entity* entity) {}


}
