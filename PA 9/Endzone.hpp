#include "GameDependency.hpp"

class Endzone : public Entity, PlayerCollidable, GameDependency {
public:

	Endzone() {}

	void handlePlayerCollision(Rectangle rect = {}) {
		if (CheckCollisionRecs(player().getRectangle(), { m_position.x, m_position.y, mapComponentDimensions, mapComponentDimensions })) {
			//game().nextLevel();
		}
	}

	// Drawing is handled in mapFactory
	void draw() {}

	void update() {
		handlePlayerCollision();
	}
};
