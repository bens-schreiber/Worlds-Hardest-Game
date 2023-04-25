#pragma once
#include <functional>
#include "PlayerCollidable.hpp"

// Green endzone for the player to go to the next level on collision
// Only used for collision testing. Drawing of the actual rectangle is handled in MapFactory
class Endzone : public Entity, PlayerCollidable {

	// Body
	Rectangle m_rect = { 0,0 };

public:

	Endzone(Rectangle rect) : m_rect(rect) {}

	// On player collision, mark levelCompleted as true. This will be caught in the next frame update.
	// Reset position in order to avoid spawning on the next endzone. This could still happen if the endzone is on the
	// players old spawnpoint, so refrain from that level behavior
	void handlePlayerCollision(Rectangle rect = {}) {
		if (CheckCollisionRecs(player().getRectangle(), m_rect)) {
			player().levelCompleted = true;
			player().resetPosition();
		}
	}

	// Drawing is handled in mapFactory
	void draw() {}

	void update() {
		handlePlayerCollision();
	}
};
