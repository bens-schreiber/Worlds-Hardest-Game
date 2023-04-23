#pragma once
#include <vector>
#include "Entity.hpp"

// Dependency injection for entities.
class EntityDependency {
	static std::vector<Entity*> m_entities;
protected:
	EntityDependency() = default;

	void addEntity(Entity* entity) { m_entities.push_back(entity); }

	std::vector<Entity*>& entities() { return m_entities; }
};