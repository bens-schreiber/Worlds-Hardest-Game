#pragma once
#include <vector>
#include <iostream>
#include "consts.hpp"
#include "MapCollidable.hpp"
#include "PlayerDependency.hpp"

struct MapComponent {
	friend class Map;
	Rectangle rectangle;
	Color color;
};

// Map class. Composed of rectangles that the player must be colliding with at all times.
class Map : public FrameListenable, PlayerDependency {
	friend class MapFactory;
	int m_height;
	std::string m_title;
	std::vector<MapComponent> m_components = {};
	std::vector<MapCollidable*> m_collidables = { playerPointer() };
	Vector2 m_spawnpoint{ 0,0 };

	void handleCollision() {

		player().resetMovement();
		for (const auto& c : m_collidables) {
			bool colliding = false;
			for (const auto& i : m_components) {
				colliding = c->checkMapCollision(i.rectangle);
				if (colliding) { break; }
			}

			if (!colliding) {
				c->handleMapOutOfBounds();
			}
		}
	}

public:
	Map() {}

	//~Map() {
	//	for (auto& i : m_collidables) {
	//		delete i;
	//	}
	//}
	
	void draw() {
		DrawText(m_title.c_str(), mapCenterX - MeasureText(m_title.c_str(), mapTitleFontSize) / 2, mapCenterY - (m_height * mapComponentDimensions) - mapTitleDisplacement, mapTitleFontSize, BLACK);
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
