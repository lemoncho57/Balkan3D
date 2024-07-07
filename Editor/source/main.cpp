#include <SDL2/SDL.h>
#include <Balkan3D/include/Logging/Loging.h>
#include <Balkan3D/include/Window.h>
#include <Balkan3D/include/Logging/Asserts.h>
#undef main

int main(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return 1;
	}
	BALKAN3D_ASSERT(true, "Unable to start SDL!");

	Window window("Hello", 1280, 720);
	window.initSDL();

	bool shouldClose = false;
	SDL_Event e;

	while (!shouldClose)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				shouldClose = true;
		}
	}

	return 0;
}