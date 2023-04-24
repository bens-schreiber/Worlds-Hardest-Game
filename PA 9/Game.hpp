#pragma once
#include <deque>
#include <vector>
#include "MapFactory.hpp"
#include "Interface.hpp"

class Game : public FrameListenable {

	friend class MapFactory;

	Player m_player = Player();

	std::deque<FrameListenable*> m_frameListenables = {};

	std::vector<std::string> m_levels = {
		"tutorial1.whg",
		"tutorial2.whg",
		"level1.whg"
	};

	Map m_map;

public:

	void initialize() {

		// Create a player entity to be the main controllable actor of the game.
		// The player is dependency injected into the PlayerCollideable interface
		PlayerDependency::setPlayer(&m_player);

		// Grab the first map
		m_map = MapFactory(m_frameListenables).mapFromFile(m_levels[0]);

		m_frameListenables.push_back(new Interface());

		// Set the players spawnpoint to the new maps spawnpoint
		m_player.setSpawnPoint(m_map.getSpawnpoint());
	}

	void update() {

		m_map.update();
		for (const auto& i : m_frameListenables) {
			i->update();
		}
		m_player.update();
	}

	void draw() {
		m_map.draw();
		for (const auto& i : m_frameListenables) {
			i->draw();
		}
		m_player.draw();

		if (m_player.levelCompleted) {
			nextLevel();
			return;
		}
	}

	void nextLevel() {
		m_player.levelCompleted = false;

		// Clear listenables
		for (auto i : m_frameListenables) {
			delete i;
		}

		m_frameListenables = { new Interface() };
		m_map = MapFactory(m_frameListenables).mapFromFile(m_levels[m_player.getLevel()]);
		m_player.incrementLevel(m_levels.size());
		m_player.setSpawnPoint(m_map.getSpawnpoint());
	}
};
