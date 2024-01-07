#include "Component.h"

#include "Entity.h"

namespace golf {


Component::Component(Entity* entity)
	:m_owner(entity) {}

void Component::kill() {
	if(m_owner != nullptr) {
		m_owner->removeComponent(*this);
		releaseFromOwner();
	}
}

void Component::setOwner(Entity* entity) {
	m_owner = entity;
}

void Component::releaseFromOwner() {
	m_owner = nullptr;
}

Entity* Component::getOwner() {
	return m_owner;
}

std::shared_ptr<Transform> Component::getTransform() {
	return m_owner->getTransform();
}


}
