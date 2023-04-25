#pragma once
#include <deque>
#include <thread>
#include <vector>
#include <list>
#include "MapFactory.hpp"
#include "Interface.hpp"
#include "AutomatedPlayer.hpp"
#include "GhostPlayers.hpp"
#define FRAME_LISTENABLES_CONSTANTS 3

class Game : public FrameListenable {

	Player* m_player;

	// game map
	Map m_map;

	// All drawable and updateable objects
	std::vector<FrameListenable*> m_frameListenables = {};

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

	// Thread for running tests
	std::thread m_testRunner;

public:

	Game() = default;


	~Game() {

		// Delete player dependency
		delete m_player;

		// Delete remaining frame listenables
		for (auto& i : m_frameListenables) {
			delete i;
		}
	}

	// Must be run before playing a game
	void useGameLevels() {

		// Create a player entity to be the main controllable actor of the game.
		// The player is dependency injected into the PlayerCollideable interface
		m_player = PlayerDependency::newPlayer();

		// Set the levels to be the normal game levels
		m_levels = m_gameLevels;

		// Interface, Map and GhostPlayers will stay in listenables until game ends
		m_frameListenables = { new Interface(), new GhostPlayers() };

		// Create the game map
		m_map = MapFactory(m_frameListenables).mapFromFile(m_levels[0]);
		m_frameListenables.insert(m_frameListenables.begin(), &m_map);

		// Set the players spawnpoint to the new maps spawnpoint
		m_player->setSpawnPoint(m_map.getSpawnpoint());
	}

	void useTestLevels() {

		// Set the levels to be the test levels
		m_levels = m_testLevels;

		// Set the player dependency to an automated player
		delete m_player;
		m_player = new AutomatedPlayer();
		PlayerDependency::setPlayer(m_player);

		// Grab the first map
		m_map = MapFactory(m_frameListenables).mapFromFile(m_testLevels[0]);

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

	// Called every frame
	void update() {
		for (const auto& i : m_frameListenables) i->update();
		m_player->update();
	}

	// called every frame
	void draw() {
		for (const auto& i : m_frameListenables) i->draw();
		m_player->draw();

		// Check for the level to be done
		if (m_player->levelCompleted) {
			nextLevel();
			return;
		}
	}

	// Go to the next level of the map
	void nextLevel() {

		m_player->incrementLevel();

		// end game
		if (m_player->getLevel() > m_levels.size() - 1) {
			exit(1);
		}

		// Reset the level completed checker
		m_player->levelCompleted = false;

		// Clear listenables
		for (auto i = m_frameListenables.size() - 1; i > FRAME_LISTENABLES_CONSTANTS; --i) {
			delete m_frameListenables[i];
			m_frameListenables.erase(m_frameListenables.begin() + i);
		}

		// Create the next map
		m_map = MapFactory(m_frameListenables).mapFromFile(m_levels[m_player->getLevel()]);
		// Set spawnpoint to the maps spawnpoint
		m_player->setSpawnPoint(m_map.getSpawnpoint());
	}
};
