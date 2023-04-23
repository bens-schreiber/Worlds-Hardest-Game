#pragma once
#include <vector>
#include "EntityDependency.hpp"

// Interface for dealing with entity collisions
// Any class that implements EntityCollidable will be able to collide with all entties and
// edit the entities movement
class EntityCollidable : protected EntityDependency {
public:

	// Collide with entity logic
	virtual void handleEntityCollision(Rectangle rect = {}) = 0;
};