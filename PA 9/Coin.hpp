#pragma once
#include "PlayerCollidable.hpp"
class Coin : public PlayerCollidable, public Entity {
	static int coinAmount;
	bool m_transparent = false;
public:
	static void resetCoins() {
		coinAmount = 0;
	}

	static bool allCoinsCollected() {
		return coinAmount <= 0;
	}

	Coin(Vector2 position) : Entity(position) {
		++coinAmount;
	}

	~Coin() {}

	void draw() {

		// BACKGROUND
		DrawCircle(m_position.x, m_position.y, ballRadius, ColorAlpha(BLACK, m_transparent ? 0.0f : 1.0f));

		// BALL
		DrawCircle(m_position.x, m_position.y, ballRadius - 7, ColorAlpha(YELLOW, m_transparent ? 0.0f : 1.0f));
		
	}
	void handlePlayerCollision(Rectangle rect = {}) {

		// If the ball and the player collide
		if (!m_transparent && CheckCollisionCircleRec(m_position, ballRadius, player().getRectangle()))
		{
			m_transparent = true;
			coinAmount--;
		}
	}


	void update() {
		handlePlayerCollision();
	}
};