#pragma once

namespace golf {

struct Transform;
class Entity;

class Component {
public:
	explicit Component(Entity* entity = nullptr);
	virtual ~Component() = default;
	Component(Component &&) = delete;
	Component(const Component &) = delete;
	Component &operator=(Component &&) = delete;
	Component &operator=(const Component &) = delete;

	virtual void kill() final;
	virtual void setOwner(Entity* entity) final;
	[[nodiscard]] virtual Entity* getOwner() final;
	[[nodiscard]] virtual Transform* getTransform() final;

protected:
	virtual void onKill();
	virtual void onOwnerSet(Entity* entity);

private:
	Entity* m_owner;
	
	friend class Entity;
};


}
