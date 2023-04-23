#pragma once
#include <vector>
#include <iostream>
#include "consts.hpp"
#include "raylib.h"
#include "PlayerCollidable.hpp"
#include "EntityCollidable.hpp"
#include "FrameListenable.hpp"

struct MapComponent {
	friend class Map;
	Rectangle rectangle;
	Color color;
};

// Map class. Composed of rectangles that the player must be colliding with at all times.
class Map : public FrameListenable, PlayerCollidable, EntityCollidable {
	friend class MapFactory;
	std::vector<MapComponent> m_components;
	Vector2 m_spawnpoint{ 0,0 };

public:
	Map() {}

	void handleCollision() {

		player().resetMovement();
		for (const auto& i : m_components) {
			handlePlayerCollision(i.rectangle);
			handleEntityCollision(i.rectangle);
		}
	}

	void handleEntityCollision(Rectangle rect = {}) {
		for (const auto& i : entities()) {
			if (CheckCollisionPointRec(i->getPosition(), rect)) {
				i->flipVelocityX();
			}
		}
	}

	// Check every single component of the map against the player.
	// Assume all movement is false (via resetMovement)
	// If the player can make a movement (UP, DOWN, RIGHT, LEFT) in the next frame (+ velocity) enable the movement
	// Else, the movement is already false.
	void handlePlayerCollision(Rectangle rect) {

		Rectangle playerRect = player().getRectangle();

		if (!player().canMoveUp && CheckCollisionRecs({
			playerRect.x, 
			playerRect.y - player().getVelocity().y - playerRect.height,
			playerRect.width, 
			playerRect.height
			}, rect)) {
			player().canMoveUp = true;
		}

		if (!player().canMoveDown && CheckCollisionRecs({
			playerRect.x,
			playerRect.y + player().getVelocity().y + playerRect.height,
			playerRect.width,
			playerRect.height
			}, rect)) {
			player().canMoveDown = true;
		}

		if (!player().canMoveRight && CheckCollisionRecs({
			playerRect.x + player().getVelocity().x + playerRect.width,
			playerRect.y,
			playerRect.width,
			playerRect.height
			}, rect)) {
			player().canMoveRight = true;
		}

		if (!player().canMoveLeft && CheckCollisionRecs({
			playerRect.x - player().getVelocity().x - playerRect.width,
			playerRect.y,
			playerRect.width,
			playerRect.height
			}, rect)) {
			player().canMoveLeft = true;
		}
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
