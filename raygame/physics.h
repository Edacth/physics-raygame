#pragma once

#include "glm/vec2.hpp"
#include "shape.h"
#include "raylib.h"

class physObject
{
public:
	physObject();

	glm::vec2 pos;
	glm::vec2 vel;

	glm::vec2 forces;

	float mass;
	float drag;

	shape collider;

	Color color;

	void tickPhys(float delta);
	void draw() const;

	// Add a continuous for with respect to mass
	void addForce(glm::vec2 force);
	// Add an instantaneous force with repsect to mass
	void addImpulse(glm::vec2 impulse);
	// Accelerates the boject w/o respect to mass
	void addAccel(glm::vec2 accel);
	// Add an instantaneous force w/o repsect to mass
	void addVelocityChange(glm::vec2 delta);
};