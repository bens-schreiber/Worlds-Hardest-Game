#include "FrameListenable.hpp"
#include "PlayerCollidable.hpp"
#include "Entity.hpp"
#include <iostream>
class Endzone : public FrameListenable, PlayerCollidable, Entity {
public:

	Endzone(Vector2 position) : Entity(position) {}

	void handlePlayerCollision(Rectangle rect = {}) {
		if (CheckCollisionRecs(player().getRectangle(), { m_position.x, m_position.y, mapComponentDimensions, mapComponentDimensions })) {
			// todo: go to next level
			std::cout << "colliding with endzone \n";
		}
	}

	// Drawing is handled in mapFactory
	void draw() {
	}

	void update() {
		handlePlayerCollision();
	}
};