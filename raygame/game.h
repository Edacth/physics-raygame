#pragma once
#include <vector>


#include "physics.h"
class game
{
	float accumulatedFixedTime;

	std::vector<physObject> physObjects;

public:
	game();

	void init();
	void tick();
	void tickPhys();
	void draw() const; // const because it shouldn't modify state
	void exit();

	bool shouldClose() const;
	bool shouldPhysics() const;

	float targetFixedStep; // Time between fixed updates
};