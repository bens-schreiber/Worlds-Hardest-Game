#include "Map.hpp"
#include "consts.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <map>

// Factory class dedicated to making Map objects
class MapFactory {

	Map m_map;
	Vector2 m_position{ 0,interfaceBarHeight};
	bool m_altColors = false;

	// checkered square
	MapComponent basicMapRectangle() {
		MapComponent c = { {m_position.x, m_position.y, mapComponentDimensions, mapComponentDimensions},  m_altColors ? mapCheckerColor : RAYWHITE };
		m_altColors = !m_altColors;
		return c;
	}

	MapComponent createMapComponent(const char& i) {
		switch (i) {
		case '@':
			m_map.m_spawnpoint = m_position;
			return basicMapRectangle();
		case '#':
			return basicMapRectangle();
		}
	}

public:

	// Creates a map from a .whgm file
	Map mapFromFile() {
		std::fstream file;
		file.open("level1.whgm", std::ios::in);
		
		std::string line;
		while (std::getline(file, line)) {
			for (const auto& i : line) {
				m_map.m_components.push_back(createMapComponent(i));
				m_position.x += mapComponentDimensions;
			}
			m_position.x = 0;
			m_position.y += mapComponentDimensions;
			m_altColors = !m_altColors;
		}


		file.close();
		return m_map;
	}
};