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

public:

	TrigBall(Vector2 position,
		Vector2 velocity, 
		int circleRadius,
		int circleSpeed)  // size of area you want to circle
		: Entity(position, velocity) {
		this->m_circleRadius = circleRadius;
		this->m_cirlceSpeed = circleSpeed;
	};

	void draw() {

		// BACKGROUND
		DrawCircle(m_position.x, m_position.y, ballRadius, BLACK);

		// BALL
		DrawCircle(m_position.x, m_position.y, ballRadius - 7, DARKBLUE);
	}
	void update() {
		m_position.x = m_position.x + m_circleRadius * (float)cos(m_cirlceSpeed * GetTime() * PI);
		m_position.y = m_position.y + m_circleRadius * (float)cos(m_cirlceSpeed * GetTime() * PI);
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

private:
	int m_circleRadius; // size of area you want to circle
	int m_cirlceSpeed; // somewhere around 0.05 is reasonable

	/*void handleMapOutOfBounds() {
		flipVelocityX();
		flipVelocityY();
	}*/
};