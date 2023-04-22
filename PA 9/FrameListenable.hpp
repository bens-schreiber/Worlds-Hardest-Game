#pragma once
#include "raylib.h"

// Base most class for all drawable and updateable things.
// Provides an interface to interact with the main raylib frame by frame loop
class FrameListenable {
public:

	// Called every frame after update
	virtual void draw() = 0;

	// Called every frame
	virtual void update() = 0;
};