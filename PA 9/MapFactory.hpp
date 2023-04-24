#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <deque>
#include "Map.hpp"
#include "LinearBall.hpp"
#include "Endzone.hpp"

// Factory class dedicated to making Map objects
class MapFactory  {

	// List of frame listenables that the map can add to
	std::deque<FrameListenable*>& m_frameListenables;

	// Map to be build by factory method
	Map m_map;

	// Position of the cursor in map
	Vector2 m_position{ mapCenterX, mapCenterY};

	// Bool for alternating the colors of the checker board
	bool m_altColors = false;

	// checkered square
	MapComponent basicMapComponent() {
		MapComponent c = { {m_position.x, m_position.y, mapComponentDimensions, mapComponentDimensions},  ((int) (m_position.x / 50) % 2) ^ ((int) (m_position.y / 50) % 2) ? mapCheckerColor : RAYWHITE};
		return c;
	}

	// green square
	MapComponent safeMapComponent() {
		return { {m_position.x, m_position.y, mapComponentDimensions, mapComponentDimensions}, mapComponentSafeColor };
	}

	// Add the ball to the frame listenables and the entity collision list
	void createXBall(bool movingRight) {

		Vector2 velocity = { movingRight ? 5.0f : -5.0f, 0.0f };
		// TODO: don't hardcode ball bounds
		auto b = new LinearBall(
			{m_position.x + ballRadius + ballRadiusOutline, m_position.y + ballRadius + ballRadiusOutline}, 
			velocity,
			{ 0, screenWidth});
		m_map.m_collidables.push_back(b);
		m_frameListenables.push_back(b);
	}

	// Add the ball to the frame listenables and the entity collision list
	void createYBall() {
		auto b = new LinearBall(m_position, { 0, 5 });
		m_frameListenables.push_back(b);
	}

	// Switch based off the char given
	MapComponent createMapComponent(const char& i) {
		switch (i) {
		case '@':
			// Spawn in the middle of the square
			m_map.m_spawnpoint = {
				m_position.x + (playerDimensions) / 2,
				m_position.y + (playerDimensions) / 2 
			};
			return safeMapComponent();
		case '#':
			return basicMapComponent();
		case '$':
			return safeMapComponent();
		case '%':
			auto c = safeMapComponent();
			m_frameListenables.push_back(new Endzone(c.rectangle));
			return c;
		case 'R':
			createXBall(true);
			return basicMapComponent();
		case 'L':
			createXBall(false);
			return basicMapComponent();
		default:
			return basicMapComponent();
		}
	}

public:

	MapFactory(std::deque<FrameListenable*>& frameListenables) 
		: m_frameListenables(frameListenables) {}

	// Creates a map from a .whg file
	// See readme for file guidelines
	Map mapFromFile(std::string fileLocation) {

		// Open file
		std::fstream file;
		file.open(fileLocation, std::ios::in);
		
		// Parse each line
		std::string line;

		// Get the map height
		std::getline(file, line);
		m_map.m_height = atoi(line.c_str());
		
		// center the map Y
		m_position.y -= m_map.m_height * mapComponentDimensions / 2;

		// Get the title
		std::getline(file, line);
		m_map.m_title = line;

		while (std::getline(file, line)) {

			// center the map X
			m_position.x -= line.size() * mapComponentDimensions / 2;

			// Parse each character
			for (const auto& i : line) {

				// 0 is blank space
				if (i != '0') {
					m_map.m_components.push_back(createMapComponent(i));
				}

				// Increment position
				m_position.x += mapComponentDimensions;
			}

			// New row, reset X position
			m_position.x = mapCenterX;
			m_position.y += mapComponentDimensions;
		}

		// Close the file
		file.close();
		return m_map;
	}
};
