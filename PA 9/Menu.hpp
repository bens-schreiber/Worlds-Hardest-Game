#pragma once

#include "Application.h"

class Menu : public FrameListenable
{
public:

	typedef enum {
		NONE = -1,
		PLAY = 0,
		TUTORIAL = 1,
		TESTS = 2
	} choices;

	const char* processChoice[3] = {
		"PLAY",
		"TUTORIAL",
		"TESTS"
	};

	const Color choiceColors[6] = {
		RED,
		DARKBLUE,
		GREEN,
		MAROON,
		DARKPURPLE,
		DARKGREEN
	};

	Rectangle toggleRecs[numChoices] = { 0 };

	void draw()
	{

		if (initRectangles)
		{
			for (int i = 0; i < numChoices; i++)
			{
				toggleRecs[i] = {
					(float)(mapCenterX * ((i + 1) / 2.0)) - (MeasureText(processChoice[i], menuChoiceFontSize) / 2),
					(float)(mapCenterY + ((mapCenterY - interfaceBarHeight) / 2)),
					(float)(MeasureText(processChoice[i], menuChoiceFontSize)),
					(float)(menuChoiceFontSize)
				};
			}

			initRectangles = false;
		}


		ClearBackground(LIGHTGRAY);

		DrawRectangle(0, 0, screenWidth, interfaceBarHeight, BLACK);
		DrawRectangle(0, screenHeight - interfaceBarHeight, screenWidth, interfaceBarHeight, BLACK);
		std::stringstream ss;
		ss << "BASED ON THE ORIGINAL GAME BY STEPHEN CRITOPH";
		DrawText(ss.str().c_str(), 30, 10, 50, WHITE);
		// clear
		ss.str("");
		ss << "MADE BY: BEN S. + KENDALL L. + ANDREW V. + ANDY M.";
		DrawText(ss.str().c_str(), 30, screenHeight - interfaceBarHeight + (screenHeight / 80), 50, WHITE);
		// clear
		ss.str("");
		ss << "THE WORLD'S";
		DrawText(ss.str().c_str(), mapCenterX - MeasureText("HARDEST GAME", menuTitleFontSize) / 2, (mapCenterY - ((mapCenterY - interfaceBarHeight) / 2) - (menuTitleFontSize / 4)), mapTitleFontSize, BLACK);
		// clear
		ss.str("");
		ss << "HARDEST GAME";
		DrawText(ss.str().c_str(), mapCenterX - MeasureText(ss.str().c_str(), menuTitleFontSize) / 2, mapCenterY - ((mapCenterY - interfaceBarHeight) / 2), menuTitleFontSize, BLUE);
		

		// Draw Rectangles to make choices and the choice's text
		for (int i = 0; i < numChoices; i++)
		{
			DrawRectangleRec(toggleRecs[i], LIGHTGRAY);
			DrawText(processChoice[i], (mapCenterX * ((i + 1) / 2.0)) - (MeasureText(processChoice[i], menuChoiceFontSize) / 2), mapCenterY + ((mapCenterY - interfaceBarHeight) / 2), menuChoiceFontSize, 
				(i == mouseHoverRec) ? choiceColors[i + numChoices] : choiceColors[i]);
		}

	};


	void update() 
	{
		Game *g = (Game*)Application::getInstance().getGame();
		// Mouse toggle group logic
		for (int i = 0; i < numChoices; i++)
		{
			if (CheckCollisionPointRec(GetMousePosition(), toggleRecs[i]))
			{
				mouseHoverRec = i;

				if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
				{
					currentChoice = i;
					choiceMade = true;
				}
				break;
			}
			else mouseHoverRec = -1;
		}

		if (choiceMade)
		{
			switch (currentChoice)
			{
				case PLAY: g->runGame(); break; // play the levels
				case TUTORIAL: g->runTutorial(); break; // play the tutorial
				case TESTS: g->runTests(); break; // run the tests
				default: break; // NONE
			}

			currentChoice = NONE;

			Application::getInstance().runGame();
		}
	};

	bool getChoiceMade(void)
	{
		return choiceMade;
	};
	void setChoiceMade(bool newChoice)
	{
		this->choiceMade = newChoice;
	}

private:

	int mouseHoverRec = -1;
	int currentChoice = NONE;
	bool choiceMade = false;
	bool initRectangles = true;
};