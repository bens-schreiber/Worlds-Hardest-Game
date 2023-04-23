#pragma once
#include <deque>
#include "FrameListenable.hpp"
#include "Player.hpp"
#include "PlayerCollidable.hpp"
#include "Map.hpp"
#include "MapFactory.hpp"
#include "Interface.hpp"
class Game : public FrameListenable {

	Player m_player = Player();

	std::deque<FrameListenable*> m_frameListenables = {};

	Map m_map = MapFactory(m_frameListenables).mapFromFile();

public:

	void initialize() {

		// Create a player entity to be the main controllable actor of the game.
		// The player is dependency injected into the PlayerCollideable interface
		PlayerDependency::setPlayer(&m_player);

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
	}

};