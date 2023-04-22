#pragma once
#include "PlayerCollidable.hpp"
#include "FrameListenable.hpp"
#include "consts.hpp"
#include <vector>
#include "raylib.h"

// Map class. Composed of rectangles that the player must be colliding with at all times.
class Map : public FrameListenable, public PlayerCollidable {
	std::vector<Rectangle> m_components = {
		{screenWidth / 2, screenHeight / 2, 200,200}
	};

public:
	Map() : PlayerCollidable() {}

	void handleCollision() {

		bool colliding = false;
		for (const auto& i : m_components) {
			bool tf = false;
			player().setOut_of_bounds_R(tf);
			player().setOut_of_bounds_L(tf);
			player().setOut_of_bounds_Up(tf);
			player().setOut_of_bounds_Down(tf);
			tf = true;

				if ((i.width + i.x) - player().getRectangle().width - playerBorderSize <= player().getRectangle().x)
				{
					player().setOut_of_bounds_R(tf);
				}
				if (i.x + playerBorderSize >= player().getRectangle().x)
				{
					player().setOut_of_bounds_L(tf);
				}
				if ((i.height + i.y) - player().getRectangle().height - playerBorderSize <= player().getRectangle().y)
				{
					player().setOut_of_bounds_Down(tf);
				}
				if (i.y + playerBorderSize >= player().getRectangle().y)
				{
					player().setOut_of_bounds_Up(tf);
				}
		}
	}
	
	void draw() {
		for (const auto& i : m_components) {
			DrawRectangleRec(i, GRAY);
		}
	}

	// Called every frame
	void update() {
		handleCollision();
	}
};
