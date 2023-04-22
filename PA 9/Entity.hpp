#pragma once
#include "raylib.h"

// Base most class for all drawable and updateable things.
// Provides an interface to interact with the main raylib frame by frame loop
class Entity {
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

	// Called every frame after update
	virtual void draw() = 0;

	// Called every frame
	virtual void update() = 0;
};