#pragma once
#include "raylib.h"
class Entity {
protected:
	Vector2 m_position;
	Vector2 m_velocity;
	Vector2 m_accelration;

	Entity(
		Vector2 m_position = { 0,0 }, 
		Vector2 m_velocity = { 0,0 }, 
		Vector2 m_acceleration = { 0,0 }) 
	{}

public:
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void handleCollision(Entity* entity) = 0;
};