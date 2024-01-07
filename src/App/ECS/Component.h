#pragma once

namespace golf {

struct Transform;
class Entity;

class Component {
public:
	explicit Component(Entity* entity = nullptr);
	virtual ~Component() = default;
	Component(Component &&) = default;
	Component(const Component &) = default;
	Component &operator=(Component &&) = default;
	Component &operator=(const Component &) = default;

	virtual void kill(); // Ta funkcja musi wykonwać Component::kill(); po overridowaniu!!!

	virtual void setOwner(Entity* entity); // Ta funkcja musiy wywoływać Component::setOwner(entity) po overridowaniu!!!
	void releaseFromOwner();
	Entity* getOwner();
	std::shared_ptr<Transform> getTransform();

private:
	Entity* m_owner;
	
	friend class Entity;
};


}
