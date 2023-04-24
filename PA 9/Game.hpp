#pragma once
#include <deque>
#include <thread>
#include <vector>
#include "MapFactory.hpp"
#include "Interface.hpp"
#include "AutomatedPlayer.hpp"

class Game : public FrameListenable {

	Player* m_player;

	std::deque<FrameListenable*> m_frameListenables = {};

	// levels to be used
	std::vector<std::string> m_levels = {};

	// Normal game levels
	std::vector<std::string> m_gameLevels = {
		"tutorial1.whg",
		"tutorial2.whg",
		"level1.whg",
		"level2.whg"
	};

	// Test game levels
	std::vector<std::string> m_testLevels{
		"test1.whgt",
		"test2.whgt",
		"test3.whgt",
		"test4.whgt",
		"test5.whgt",
	};

	std::thread m_testRunner;

	Map m_map;

public:

	~Game() {
		delete m_player;
	}

	void initialize() {

		// Set the levels to be the normal game levels
		m_levels = m_gameLevels;

		// Create a player entity to be the main controllable actor of the game.
		// The player is dependency injected into the PlayerCollideable interface
		delete m_player;
		m_player = new Player();
		PlayerDependency::setPlayer(m_player);

		// Grab the first map
		m_map = MapFactory(m_frameListenables).mapFromFile(m_levels[0]);

		m_frameListenables.push_back(new Interface());

		// Set the players spawnpoint to the new maps spawnpoint
		m_player->setSpawnPoint(m_map.getSpawnpoint());
	}

	void runTests() {

		// Set the levels to be the test levels
		m_levels = m_testLevels;

		// Set the player dependency to an automated player
		delete m_player;
		m_player = new AutomatedPlayer();
		PlayerDependency::setPlayer(m_player);

		// Grab the first map
		m_map = MapFactory(m_frameListenables).mapFromFile(m_testLevels[0]);

		m_frameListenables.push_back(new Interface());

		// Set the players spawnpoint to the new maps spawnpoint
		m_player->setSpawnPoint(m_map.getSpawnpoint());

		// Finish level after testDuration seconds
		m_testRunner = std::thread([&]() {
			while (1) {
				std::this_thread::sleep_for(std::chrono::seconds(testDuration));
				m_player->levelCompleted = true;
			}
		});
	}

	void update() {
		m_map.update();
		for (const auto& i : m_frameListenables) i->update();
		m_player->update();
	}

	void draw() {

		m_map.draw();
		for (const auto& i : m_frameListenables) i->draw();
		m_player->draw();
		if (m_player->levelCompleted) nextLevel();
	}

	void nextLevel() {

		// end game
		if (m_player->getLevel() > m_levels.size() - 1) {
			exit(1);
		}

		// Reset the level completed checker
		m_player->levelCompleted = false;

		// Clear listenables
		for (auto i : m_frameListenables) {
			delete i;
		}

		// Add interface to the listenables
		m_frameListenables = { new Interface() };

		// Create the next map
		m_map = MapFactory(m_frameListenables).mapFromFile(m_levels[m_player->getLevel()]);

		m_player->incrementLevel();

		// Set spawnpoint to the maps spawnpoint
		m_player->setSpawnPoint(m_map.getSpawnpoint());
	}
};
