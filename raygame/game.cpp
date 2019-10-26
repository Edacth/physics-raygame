#include "game.h"

#include "raylib.h"
#include <iostream>

game::game()
{
	targetFixedStep = 1.0f / 30.0f;
	accumulatedFixedTime = 0.0f;
}

void game::init()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	screenWidth = 800;
	screenHeight = 450;
	screenWrap = true;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------
}

void game::tick()
{
	// do update
	accumulatedFixedTime += GetFrameTime();

	bool mb0 = IsMouseButtonPressed(0);
	bool mb1 = IsMouseButtonPressed(1);

	if (mb0 || mb1)
	{
		physObjects.emplace_back();
		std::cout << "Added a physics object!" << std::endl;

		auto& babyPhys = physObjects[physObjects.size() - 1];
		auto mousePos = GetMousePosition();
		babyPhys.pos = { mousePos.x, mousePos.y };

		if (mb0)
		{
			babyPhys.collider = circle{ 15.0f };
			babyPhys.addForce({ 20000.0f, 0.0f });
			babyPhys.drag = 0;
			babyPhys.color = BLUE;
		}
		else
		{
			//babyPhys.collider = aabb{ {15, 15} };
			babyPhys.collider = circle{ 15.0f };
			babyPhys.addForce({ -20000.0f, 0.0f });
			babyPhys.drag = 0;
			babyPhys.color = RED;
		}
	}
}

void game::tickPhys()
{
	// do physics
	accumulatedFixedTime -= targetFixedStep;

	//std::cout << "PHYS TICK" << std::endl;
	for (auto& i : physObjects)
	{
		i.tickPhys(targetFixedStep);
	}

	for (auto& i : physObjects)
	{
		// check collision against other physObjects
		for (auto &j : physObjects)
		{
			if (&i == &j) { continue; }

			bool collision = false;

			i.collider.match([i, j, &collision](circle c) { if (checkCircleX(i.pos, c, j.pos, j.collider)) { collision = true; } },
							 [i, j, &collision](aabb a) {if (checkAABBX(i.pos, a, j.pos, j.collider)) { collision = true; }});

			if (collision) { resolvePhysBodies(i, j); }
		}

		// do screenwrap if enabled
		if (screenWrap)
		{
			// check if below play area
			if (i.pos.y > (float)screenHeight)
			{
				i.pos.y -= screenHeight;
			}
			// check if above play area
			else if (i.pos.y < 0.0f)
			{
				i.pos.y += screenHeight;
			}
			// check if right of play area
			if (i.pos.x > (float)screenWidth)
			{
				i.pos.x -= screenWidth;
			}
			//check if left of play area
			else if (i.pos.x < 0.0f)
			{
				i.pos.x += screenWidth;
			}
		}
		
	}
}

void game::draw() const
{
	// Draw
	//----------------------------------------------------------------------------------
	BeginDrawing();

	ClearBackground(RAYWHITE);

	for (const auto& i : physObjects)
	{
		i.draw();
	}

	EndDrawing();
	//----------------------------------------------------------------------------------
}

void game::exit()
{
	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------
}

bool game::shouldClose() const
{
	return WindowShouldClose();
}

bool game::shouldPhysics() const
{
	return accumulatedFixedTime >= targetFixedStep;
}
