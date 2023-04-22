#pragma once
#include "raylib.h"
class Entity {
protected:
	Vector2 m_position;
	Vector2 m_velocity;
	Vector2 m_acceleration;

	Entity(
		Vector2 position = { 0,0 },
		Vector2 velocity = { 0,0 },
		Vector2 acceleration = { 0,0 }) : m_position(position), m_velocity(velocity), m_acceleration(acceleration) 
	{}

public:
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void handleCollision(Entity* entity) = 0;
};