#pragma once
#include "Game.hpp"

// Dependency injection for getting the Game
class GameDependency {
	static Game* m_game;

public:

	GameDependency() {}

	static void setGame(Game *game) {
		m_game = game;
	}

protected:
	Game& game() {
		return *m_game;
	}
};
