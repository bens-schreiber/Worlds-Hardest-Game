#pragma once
#include <deque>
#include <thread>
#include <vector>
#include <list>
#include "MapFactory.hpp"
#include "Interface.hpp"
#include "AutomatedPlayer.hpp"
#include "GhostPlayers.hpp"

class Game : public FrameListenable {

	// The player to be interacting with the game.
	Player* m_player;

	// game map
	Map *m_map;

	// All drawable and updateable objects
	std::vector<FrameListenable*> m_frameListenables = {};

	// Static listenables that are not deleted every level
	std::vector<FrameListenable*> m_staticFrameListenables = {};

	// levels to be used
	std::vector<std::string> m_levels = {};

	// Normal game levels
	std::vector<std::string> m_gameLevels = {
		"tutorial1.whg",
		"tutorial2.whg",
		"level1.whg",
		"level2.whg",
		"level5.whg",
		"level3.whg",
		"level7.whg"
	};

	// Test game levels
	std::vector<std::string> m_testLevels{
		"test1.whgt",
		"test2.whgt",
		"test3.whgt",
		"test4.whgt",
		"test5.whgt"
	};

	// Thread for running tests
	std::thread m_testRunner;

public:

	Game() = default;

	~Game() {

		// Delete remaining frame listenables
		for (auto& i : m_frameListenables) {
			delete i;
		}

		for (auto& i : m_staticFrameListenables) {
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

		// Create the game map, populate the listenables
		m_map = MapFactory(m_frameListenables).mapFromFile(m_levels[0]);

		// Interface and GhostPlayers will stay in listenables until game ends
		m_staticFrameListenables = { new Interface(), new GhostPlayers(), m_player };

		// Set the players spawnpoint to the new maps spawnpoint
		m_player->setSpawnPoint(m_map->getSpawnpoint());
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
		m_player->setSpawnPoint(m_map->getSpawnpoint());

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
		for (const auto& i : m_staticFrameListenables) i->update();
	}

	// called every frame
	void draw() {
		for (const auto& i : m_frameListenables) i->draw();
		for (const auto& i : m_staticFrameListenables) i->draw();

		// Check for the level to be done
		// This check must be done in draw to prevent the screen from tearing
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
		for (auto& i : m_frameListenables) delete i;
		m_frameListenables.clear();

		// Create the next map
		m_map = MapFactory(m_frameListenables).mapFromFile(m_levels[m_player->getLevel()]);

		m_frameListenables[0] = m_map;

		// Set spawnpoint to the maps spawnpoint
		m_player->setSpawnPoint(m_map->getSpawnpoint());
	}
};
