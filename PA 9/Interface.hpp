#pragma once

#include "PlayerDependency.hpp"
#include <sstream>

class Interface : public FrameListenable, PlayerDependency
{
public:
	Interface() : PlayerDependency()
		{};

	void draw()
	{
		DrawRectangle(0, 0, screenWidth, interfaceBarHeight, BLACK);
		 
		std::stringstream ss;
		ss << "FAILS: " << player().getDeaths();
		DrawText(ss.str().c_str(), 30, 10, 50, WHITE);

		// clear
		ss.str("");
		ss << "LEVEL: " << player().getLevel();

		DrawText(ss.str().c_str(), 1500, 10, 50, WHITE);
		DrawRectangle(0, screenHeight - interfaceBarHeight, screenWidth, interfaceBarHeight, BLACK);
	}

	// Updates are given by the player dependency
	void update() {}
};
