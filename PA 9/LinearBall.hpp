#pragma once

#include "consts.hpp"
#include "MapCollidable.hpp"
#include "PlayerCollidable.hpp"

// Ball capable of moving linearly along the X or Y
class LinearBall : public Entity, public MapCollidable, PlayerCollidable
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

		handlePlayerCollision();
	}
	void handlePlayerCollision(Rectangle rect = {}) {

		// If the ball and the player collide
		if (!player().isDead() && CheckCollisionCircleRec(m_position, ballRadius, player().getRectangle()))
		{
			player().killPlayer();
		}

	}

	bool checkMapCollision(Rectangle rect = {}) {
		return CheckCollisionCircleRec({ m_position.x, m_position.y }, 0, rect);
	}

	void handleMapOutOfBounds() {
		flipVelocityX();
		flipVelocityY();
	}
};
