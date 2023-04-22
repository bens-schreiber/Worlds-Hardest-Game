#pragma once

#include "consts.hpp"
#include "FrameListenable.hpp"

class Interface : public FrameListenable
{
public:

	Interface() {};

	void draw()
	{
		DrawRectangle(0, 0, screenWidth, barHeight, BLACK);
		DrawText("LEVEL: 1", 30, 10, 50, WHITE);
		DrawText("FAILS: 0", screenWidth - 250, 10, 50, WHITE);
		DrawRectangle(0, screenHeight - barHeight, screenWidth, barHeight, BLACK);
	}

	void update()
	{

	}
};