#pragma once
#include "PlayerCollidable.hpp"
#include "FrameListenable.hpp"
#include "consts.hpp"
#include <vector>
#include "raylib.h"

// Map class. Composed of rectangles that the player must be colliding with at all times.
class Map : public FrameListenable, public PlayerCollidable {
	std::vector<Rectangle> m_components = {
		{screenWidth / 2, screenHeight / 2, 200,200}
	};

public:
	Map() : PlayerCollidable() {}

	void handleCollision() {

		bool colliding = false;
		for (const auto& i : m_components) {
			if (CheckCollisionRecs(i, player().getRectangle())) {
				colliding = true;
				break;
			}
		}

		if (colliding) return;
		player().resetPosition();
	}
	
	void draw() {
		for (const auto& i : m_components) {
			DrawRectangleRec(i, GRAY);
		}
	}

	// Called every frame
	void update() {
		handleCollision();
	}
};
