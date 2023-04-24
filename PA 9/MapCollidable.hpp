#pragma once
#include "raylib.h"
// Interface for dealing with map collisions
class MapCollidable {
public:

	// Collide with map logic
	virtual bool checkMapCollision(Rectangle rect = {}) = 0;
	virtual void handleMapOutOfBounds() = 0;
};
