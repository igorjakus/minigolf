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

	virtual void kill();

	void setOwner(Entity* entity);
	void releaseFromOwner();
	Entity* getOwner();
	Transform* getTransform();

private:
	Entity* m_owner;
	
	friend class Entity;
};


}
