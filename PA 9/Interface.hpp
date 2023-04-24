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
		DrawRectangle(0, screenHeight - interfaceBarHeight, screenWidth, interfaceBarHeight, BLACK);
	}

	void update()
	{

	}

	// Do nothing for collision
	void handlePlayerCollision(Rectangle rect) {}
};
