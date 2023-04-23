#include <vector>
#include "Entity.hpp"
class EntityCollidable {
	static std::vector<Entity*> m_entities;
protected:
	EntityCollidable() = default;

	void addEntity(Entity* entity) { m_entities.push_back(entity); }

	std::vector<Entity*>& entities() { return m_entities; }

	virtual void handleEntityCollision() = 0;
};