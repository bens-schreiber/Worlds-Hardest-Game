#pragma once

#include "consts.hpp"
#include "MapCollidable.hpp"
#include "PlayerCollidable.hpp"
#include <time.h>
#include <math.h>

// Ball capable of moving linearly along the X or Y
class TrigBall : public Entity, public MapCollidable, PlayerCollidable
{

	//Vector2 m_boundsX;	// x lower, y higher
	//Vector2 m_boundsY;	// x lower, y higher
	int circleRadius; // size of area you want to circle

public:

	TrigBall(Vector2 position,
		Vector2 velocity, 
		int circleRadius)  // size of area you want to circle
		: Entity(position, velocity) {};

	void draw() {

		// BACKGROUND
		DrawCircle(m_position.x, m_position.y, ballRadius, BLACK);

		// BALL
		DrawCircle(m_position.x, m_position.y, ballRadius - 7, DARKBLUE);
	}
	void update() {
		m_position.x = m_position.x + circleRadius * (float)cos(0.05 * GetTime() * PI);
		m_position.y = m_position.y + circleRadius * (float)cos(0.05 * GetTime() * PI);
		handlePlayerCollision();
	}
	void handlePlayerCollision(Rectangle rect = {}) {

		// If the ball and the player collide
		if (CheckCollisionCircleRec(m_position, ballRadius, player().getRectangle()))
		{
			player().resetPosition();
			player().incrementDeaths();
		}
	}

	bool checkMapCollision(Rectangle rect = {}) {
		return CheckCollisionCircleRec({ m_position.x, m_position.y }, 0, rect);
	}

	/*void handleMapOutOfBounds() {
		flipVelocityX();
		flipVelocityY();
	}*/
};