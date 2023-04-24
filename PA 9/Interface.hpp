#pragma once

#include "PlayerDependency.hpp"
#include <sstream>

class Interface : public FrameListenable, PlayerDependency
{
public:
	int i = 0;
	Interface() : PlayerDependency()
		{};

	void draw()
	{
		DrawRectangle(0, 0, screenWidth, interfaceBarHeight, BLACK);
		 
		std::stringstream ss;
		ss << "FAILS: " << player().getDeaths();
		DrawText(ss.str().c_str(), 30, 10, 50, WHITE);
		std::stringstream s;
		if (player().getLevel() == 0) {
			s << "LEVEL: " << player().getLevel();
		}
		else {
			s << "LEVEL: " << player().getLevel() - 1;
		}
		DrawText(s.str().c_str(), 1500, 10, 50, WHITE);
		DrawRectangle(0, screenHeight - interfaceBarHeight, screenWidth, interfaceBarHeight, BLACK);
	}

	void update()
	{

	}

	// Do nothing for collision
	void handlePlayerCollision(Rectangle rect) {}
};
