#pragma once

#include "Entity.hpp"
#include "consts.hpp"
#include "raylib.h"
#include "PlayerCollidable.hpp"

// Ball capable of moving linearly along the X or Y
class LinearBall : public Entity, PlayerCollidable
{

	Vector2 m_boundsX;	// x lower, y higher
	Vector2 m_boundsY;	// x lower, y higher

public:

	LinearBall(Vector2 position, 
		Vector2 velocity, 
		Vector2 boundsX = { ballRadius, screenWidth - ballRadius },
		Vector2 boundsY = { ballRadius + interfaceBarHeight , screenHeight - ballRadius - interfaceBarHeight }
	) : Entity(position, velocity), m_boundsX(boundsX), m_boundsY(boundsY)
	{}

	void draw() {

		// BACKGROUND
		DrawCircle(m_position.x, m_position.y, ballRadius, BLACK);

		// BALL
		DrawCircle(m_position.x, m_position.y, ballRadius - 7, DARKBLUE);
	}
	void update() {

		// Increment the ball position in respect to its velocity
		m_position.x += m_velocity.x;
		m_position.y += m_velocity.y;

		if (m_position.y >= m_boundsY.y)
		{
			flipVelocityY();
		}
		if (m_position.y <= m_boundsY.x)
		{
			flipVelocityY();
		}
		if (m_position.x >= m_boundsX.y)
		{
			flipVelocityX();
		}
		if (m_position.x <= m_boundsX.x)
		{
			flipVelocityX();
		}

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
};
