#pragma once
#include <vector>
#include <deque>
#include <iostream>
#include "consts.hpp"
#include "MapCollidable.hpp"
#include "PlayerDependency.hpp"
#include "AutomatedPlayer.hpp"

// Each component of the map. Rectangle with color.
struct MapComponent {
	Rectangle rectangle;
	Color color;
};

// The contains the map scenegraph
// Each map component defines a border checks against MapCollidables every frame
// Instantiable via MapFactory
class Map : public FrameListenable, PlayerDependency {
	friend class MapFactory;

	// The height of the map. Useful for calcuating where the map title should sit on the screen.
	// Generally, it should be the amount of rows in the .whg file.
	int m_height;

	// Title to be displayed above the map
	std::string m_title;

	// For debug runs, the map will contain a set of automated instructions for an AutomatedPlayer
	std::deque<char> m_automatedInstructions;

	// All squares of the map.
	std::vector<MapComponent> m_components;

	// All things that should have some behavior when colliding with the map squares
	std::vector<MapCollidable*> m_collidables;

	// Spawnpoint for the game. Set the Player to this spawnpoint.
	Vector2 m_spawnpoint;

	// Handle collision between all map collidables
	void handleCollision() {

		// Reset the movement locks on the player each frame
		player().resetMovement();

		// If any collidables are not colliding with at least one component, call the out of bounds handler.
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

	Map() : m_collidables{playerPointer()} {}

public:

	~Map() {
		for (auto& i : m_collidables) {
			delete i;
		}
	}
	
	void draw() {

		// Draw the map title
		DrawText(m_title.c_str(), mapCenterX - MeasureText(m_title.c_str(), mapTitleFontSize) / 2, mapCenterY - (m_height * mapComponentDimensions) - mapTitleDisplacement, mapTitleFontSize, BLACK);
		
		// Render each component
		for (const auto& i : m_components) {
			DrawRectangleRec(i.rectangle, i.color);
		}
	}

	void update() {
		handleDebugInstructions();
		handleCollision();
	}

	// For debug runs
	void handleDebugInstructions() {
		if (m_automatedInstructions.size() > 0) {

			// Player must be the automated player if instructions are found.
			AutomatedPlayer* p = (AutomatedPlayer*)&player();

			// Automate player movement
			p->move(m_automatedInstructions.front());
			m_automatedInstructions.pop_front();
		}
	}

	Vector2 getSpawnpoint() const {
		return m_spawnpoint;
	}
};
