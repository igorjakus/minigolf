#include "Component.h"

#include "Entity.h"

namespace golf {


Component::Component(Entity* entity)
	:m_owner(entity) {}

void Component::kill() {
	releaseFromOwner();
}

void Component::setOwner(Entity* entity) {
	m_owner = entity;
}

void Component::releaseFromOwner() {
	setOwner(nullptr);
}

Entity* Component::getOwner() {
	return m_owner;
}

Transform* Component::getTransform() {
	return m_owner->getTransform();
}


}
