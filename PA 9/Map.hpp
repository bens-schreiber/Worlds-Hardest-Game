#pragma once
#include "PlayerCollidable.hpp"
#include "FrameListenable.hpp"
#include "consts.hpp"
#include <vector>
#include "raylib.h"

struct MapComponent {
	friend class Map;
	Rectangle rectangle;
	Color color;
};

class MapFactory;

// Map class. Composed of rectangles that the player must be colliding with at all times.
class Map : public FrameListenable, public PlayerCollidable {
	friend class MapFactory;
	std::vector<MapComponent> m_components;
	Vector2 m_spawnpoint{ 0,0 };

public:
	Map() : PlayerCollidable() {}

	void handleCollision() {

		bool colliding = false;
		for (const auto& i : m_components) {
			if (CheckCollisionRecs(i.rectangle, player().getRectangle())) {
				colliding = true;
				break;
			}
		}

		if (colliding) return;
		player().resetPosition();
	}
	
	void draw() {
		for (const auto& i : m_components) {
			DrawRectangleRec(i.rectangle, i.color);
		}
	}

	// Called every frame
	void update() {
		handleCollision();
	}

	Vector2 getSpawnpoint() const {
		return m_spawnpoint;
	}
};
