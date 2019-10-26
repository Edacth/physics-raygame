#include "physics.h"

#include "raylib.h"

physObject::physObject()
{
	pos = { 0, 0 };
	vel = { 0,0 };
	forces = { 0,0 };

	mass = 1.0f;
	drag = 1.0f;

	color = RED;
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
	float drawRadius = 15.0f;
	collider.match([this](circle s) {DrawCircle(pos.x, pos.y, s.radius, color); },
				   [this](aabb s)	{DrawRectangle(pos.x - s.halfExtents.x, pos.y - s.halfExtents.y, s.halfExtents.x * 2, s.halfExtents.y * 2, color); } );
}

void physObject::addForce(glm::vec2 force)
{
	forces += force * (1.0f / mass);
}

void physObject::addImpulse(glm::vec2 impulse)
{
	vel += impulse * (1.0f / mass);
}

void physObject::addAccel(glm::vec2 accel)
{
	// TODO: implement this
	assert(false);
}

void physObject::addVelocityChange(glm::vec2 delta)
{
	vel += delta;
}
