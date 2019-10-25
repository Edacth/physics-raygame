#include "physics.h"

#include "raylib.h"

physObject::physObject()
{
	pos = { 0, 0 };
	vel = { 0,0 };
	forces = { 0,0 };

	mass = 1.0f;
	drag = 1.0f;
}

void physObject::tickPhys(float delta)
{
	// intergrating forces into velocity
	vel += forces * delta;
	forces = { 0, 0 };

	// integrate linear drag into velocity
	vel = vel * (1.0f - delta * drag);

	// integrating velocity into position
	pos += vel * delta;
}

void physObject::draw() const
{
	DrawCircle(pos.x, pos.y, 15.0f, RED);
	DrawCircle(pos.x, pos.y, 13.0f, RAYWHITE);
}

void physObject::addForce(glm::vec2 force)
{
	forces += force * (1.0f / mass);
}