#include <vector>
#include "Entity.hpp"
#include "EntityDependency.hpp"
class EntityCollidable : protected EntityDependency {
public:
	virtual void handleEntityCollision() = 0;
};