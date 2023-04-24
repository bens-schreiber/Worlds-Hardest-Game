#pragma once
#include "Player.hpp"
class AutomatedPlayer : public Player {

public:
	AutomatedPlayer() : Player() {}

	// Ignore WASD
	void update() override {
		// Set the player rectangle position
		m_rectangle.x = m_position.x;
		m_rectangle.y = m_position.y;
	}

	void move(char i) {
		switch (i) {
		case 'W': W(); break;
		case 'A': A(); break;
		case 'S': S(); break;
		case 'D': D(); break;
		}
	}

	void W() {
		if (!canMoveUp) return;
		m_position.y -= m_velocity.y;
	}

	void A() {
		if (!canMoveLeft) return;
		m_position.x -= m_velocity.x;
	}

	void S() {
		if (!canMoveDown) return;
		m_position.y += m_velocity.y;
	}

	void D() {
		if (!canMoveRight) return;
		m_position.x += m_velocity.x;
	}
};