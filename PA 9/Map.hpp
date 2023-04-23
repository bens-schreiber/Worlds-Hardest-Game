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

		Rectangle playerRect = player().getRectangle();

		bool outUp = true;
		bool outDown = true;
		bool outRight = true;
		bool outLeft = true;
		for (const auto& i : m_components) {
			Rectangle rect = i.rectangle;
			if (outUp && CheckCollisionRecs({
				playerRect.x, 
				playerRect.y - player().getVelocity().y - playerRect.height,
				playerRect.width, 
				playerRect.height
				}, rect)) {
				outUp = false;
			}

			if (outDown && CheckCollisionRecs({
				playerRect.x,
				playerRect.y + player().getVelocity().y + playerRect.height,
				playerRect.width,
				playerRect.height
				}, rect)) {
				outDown = false;
			}

			if (outRight && CheckCollisionRecs({
				playerRect.x + player().getVelocity().x + playerRect.width,
				playerRect.y,
				playerRect.width,
				playerRect.height
				}, rect)) {
				outRight = false;
			}
			if (outLeft && CheckCollisionRecs({
				playerRect.x - player().getVelocity().x - playerRect.width,
				playerRect.y,
				playerRect.width,
				playerRect.height
				}, rect)) {
				outLeft = false;
			}

		}

		player().setOutOfBoundsUp(outUp);
		player().setOutOfBoundsDown(outDown);
		player().setOutOfBoundsR(outRight);
		player().setOutOfBoundsL(outLeft);
	}
	
	void draw() {
		for (const auto& i : m_components) {
			DrawRectangleRec(i.rectangle, i.color);
		}
	}

	void update() {
		handleCollision();
	}

	Vector2 getSpawnpoint() const {
		return m_spawnpoint;
	}
};
