#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "consts.hpp"
#include "LinearBall.hpp"
#include "Map.hpp"

// Factory class dedicated to making Map objects
class MapFactory : EntityDependency {

	// List of frame listenables that the map can add to
	std::vector<FrameListenable*>& m_frameListenables;

	// Map to be build by factory method
	Map m_map;

	// Position of the cursor in map
	Vector2 m_position{ 0,interfaceBarHeight};

	// Bool for alternating the colors of the checker board
	bool m_altColors = false;

	// checkered square
	MapComponent basicMapComponent() {
		MapComponent c = { {m_position.x, m_position.y, mapComponentDimensions, mapComponentDimensions},  m_altColors ? mapCheckerColor : RAYWHITE };
		return c;
	}

	// green square
	MapComponent safeMapComponent() {
		return { {m_position.x, m_position.y, mapComponentDimensions, mapComponentDimensions}, mapComponentSafeColor };
	}

	// Add the ball to the frame listenables and the entity collision list
	void createXBall() {
		auto b = new LinearBall(m_position, { 5, 0 });
		addEntity(b);
		m_frameListenables.push_back(b);
	}

	// Add the ball to the frame listenables and the entity collision list
	void createYBall() {
		auto b = new LinearBall(m_position, { 0, 5 });
		addEntity(b);
		m_frameListenables.push_back(b);
	}

	// Switch based off the char given
	MapComponent createMapComponent(const char& i) {
		switch (i) {
		case '@':
			m_map.m_spawnpoint = m_position;
			return safeMapComponent();
		case '#':
			return basicMapComponent();
		case '$':
			return safeMapComponent();
		case 'X':
			createXBall();
			return basicMapComponent();
		case 'Y':
			createYBall();
			return basicMapComponent();
		default:
			return basicMapComponent();
		}
	}

public:

	MapFactory(std::vector<FrameListenable*>& frameListenables) 
		: m_frameListenables(frameListenables) {}

	// Creates a map from a .whgm file
	Map mapFromFile() {

		// Open file
		std::fstream file;
		file.open("level1.whgm", std::ios::in);
		
		// Parse each line
		std::string line;
		while (std::getline(file, line)) {
			
			// Parse each character
			for (const auto& i : line) {

				// 0 is blank space, ignore if so
				if (i != '0') {
					m_map.m_components.push_back(createMapComponent(i));
				}

				// Increment position
				m_position.x += mapComponentDimensions;

				// Flip bool for alternating checker pattern
				m_altColors = !m_altColors;
			}

			// New row, set position to 0
			m_position.x = 0;
			m_position.y += mapComponentDimensions;

			// Flip bool for alternating checker pattern
			m_altColors = !m_altColors;
		}

		// Close the file
		file.close();
		return m_map;
	}
};