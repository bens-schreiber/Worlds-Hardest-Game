#pragma once

#include "consts.hpp"
#include "MapCollidable.hpp"
#include "PlayerCollidable.hpp"
#include <time.h>
#include <math.h>

// Ball capable of moving in circle
class TrigBall : public Entity, public MapCollidable, PlayerCollidable
{

	//Vector2 m_boundsX;	// x lower, y higher
	//Vector2 m_boundsY;	// x lower, y higher

public:

	TrigBall(Vector2 position,
		float circleRadius, // size of area you want to circle
		float circleSpeed)  // speed of ball
		: Entity(position), m_circleRadius(circleRadius), m_circleSpeed(circleSpeed), m_x(position.x), m_y(position.y) {}

	void draw() {

		// BACKGROUND
		DrawCircle(m_position.x, m_position.y, ballRadius, BLACK);

		// BALL
		DrawCircle(m_position.x, m_position.y, ballRadius - 7, DARKBLUE);
	}
	void update() {
		m_position.x = m_x + m_circleRadius * (float)cos(m_circleSpeed * GetTime() * PI);
		m_position.y = m_y + m_circleRadius * (float)sin(m_circleSpeed * GetTime() * PI);
		handlePlayerCollision();
	}
	void handlePlayerCollision(Rectangle rect = {}) {

		// If the ball and the player collide
		if (CheckCollisionCircleRec(m_position, ballRadius, player().getRectangle()))
		{
			player().killPlayer();
		}
	}

	bool checkMapCollision(Rectangle rect = {}) {
		return CheckCollisionCircleRec({ m_position.x, m_position.y }, 0, rect);
	}

	void handleMapOutOfBounds() {

	}

private:
	float m_circleRadius; // size of area you want to circle
	float m_circleSpeed; // somewhere around 0.5 is reasonable
	float m_x;
	float m_y;
};