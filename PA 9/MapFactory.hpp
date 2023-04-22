#include "Map.hpp"
#include "consts.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <map>

class MapFactory {

	const std::map<std::string, std::string> charToMapComp = {
		{"@","a"},
	};

	Map m_map;
	Vector2 m_position{ 0,0 };
	bool m_altColors = false;

public:

	MapComponent basicMapRectangle() {
		MapComponent c = { {m_position.x, m_position.y, mapComponentWidth, mapComponentWidth},  m_altColors ? GRAY : DARKGRAY };
		m_altColors = !m_altColors;
		return c;
	}

	MapComponent createMapComponent(const char &i) {
		switch (i) {
		case '@':
			m_map.m_spawnpoint = m_position;
			return basicMapRectangle();
		case '#':
			return basicMapRectangle();
		}
	}

	Map mapFromFile() {
		std::fstream file;
		file.open("level1.whgm", std::ios::in);
		
		std::string line;
		while (std::getline(file, line)) {
			for (const auto& i : line) {
				m_map.m_components.push_back(createMapComponent(i));
				m_position.x += mapComponentWidth;
			}
			m_position.x = 0;
			m_position.y += mapComponentWidth;
			m_altColors = !m_altColors;
		}


		file.close();
		return m_map;
	}
};