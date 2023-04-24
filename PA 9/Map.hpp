#pragma once
#include <vector>
#include <deque>
#include <iostream>
#include "consts.hpp"
#include "MapCollidable.hpp"
#include "PlayerDependency.hpp"
#include "AutomatedPlayer.hpp"

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
	std::deque<char> m_automatedInstructions;
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
		if (m_automatedInstructions.size() > 0) {

			// Player must be the automated player if instructions are found.
			AutomatedPlayer* p = (AutomatedPlayer*) &player();

			// Automate player movement
			p->move(m_automatedInstructions.front());
			m_automatedInstructions.pop_front();
		}
		handleCollision();
	}

	Vector2 getSpawnpoint() const {
		return m_spawnpoint;
	}
};
