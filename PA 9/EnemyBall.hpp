#pragma once

#include "Entity.hpp"
#include "const.h"
#include "raylib.h"
#include "PlayerCollidable.hpp"

class EnemyBall : public Entity, public PlayerCollidable
{
public:

	EnemyBall(Player* player, Vector2 position, Vector2 velocity) : Entity(position, velocity), PlayerCollidable(player)
	{}

	void draw() {
		DrawCircle(m_position.x, m_position.y, radius, BLACK);
		DrawCircle(m_position.x, m_position.y, radius - 7, DARKBLUE);
	}
	void update() {
		m_position.x += m_velocity.x;
		m_position.y += m_velocity.y;

		if (m_position.y >= screenHeight - radius)
		{
			m_velocity.y *= -1; // change directions
		}
		if (m_position.y <= radius)
		{
			m_velocity.y *= -1;
		}
		if (m_position.x >= screenWidth - radius)
		{
			m_velocity.x *= -1;
		}
		if (m_position.x <= radius)
		{
			m_velocity.x *= -1;
		}
		handleCollision();
	}
	void handleCollision() {
		if (CheckCollisionCircleRec(m_position, radius, m_player->getRectangle()))
		{
			m_player->resetPosition();
		}
	}
};
