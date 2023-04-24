#pragma once
#include <functional>
#include "PlayerCollidable.hpp"
class Endzone : public Entity, PlayerCollidable {
	Rectangle m_rect;
public:

	Endzone(Rectangle rect) : m_rect(rect) {}

	void handlePlayerCollision(Rectangle rect = {}) {
		if (CheckCollisionRecs(player().getRectangle(), m_rect)) {
			player().levelCompleted = true;
		}
	}

	// Drawing is handled in mapFactory
	void draw() {}

	void update() {
		handlePlayerCollision();
	}
};
