#include "raylib.h"

#include "game.h"

int main()
{
	game app;
	app.init();
	app.targetFixedStep = 1.0f / 30; // target physics tick rate

	// Main game loop
	while (!app.shouldClose())    // Detect window close button or ESC key
	{
		app.tick();

		while (app.shouldPhysics())
		{
			app.tickPhys();
		}

		app.draw();
	}

	app.exit();
	
	return 0;
}