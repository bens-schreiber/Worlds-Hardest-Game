#pragma once
#include "raylib.h"
#include "FrameListenable.hpp"

// Entities are objects that have some physics/movement to be acted upon each frame
class Entity : public FrameListenable {
protected:

	// Position: X,Y
	Vector2 m_position;

	// Velocity: X,Y
	Vector2 m_velocity;

	// Acceleration: X,Y
	Vector2 m_acceleration;

	Entity(
		Vector2 position = { 0,0 },
		Vector2 velocity = { 0,0 },
		Vector2 acceleration = { 0,0 }) : m_position(position), m_velocity(velocity), m_acceleration(acceleration) 
	{}

public:
	Vector2 getVelocity() const {
		return m_velocity;
	}

	Vector2 getPosition() const {
		return m_position;
	}

	void flipVelocityX() {
		m_velocity.x *= -1.0f;
	}

	void flipVelocityY() {
		m_velocity.y *= -1.0f;
	}
};