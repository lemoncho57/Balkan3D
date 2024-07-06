#include <SDL2/SDL.h>
#include <Balkan3D/include/Log/Loging.h>
#include <Balkan3D/include/Window.h>
#undef main

int main()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		LOG_FATAL("Unable to start SDL!");

	Window window("Hello", 1280, 720);
	window.initSDL();

	bool shouldClose = false;
	SDL_Event e;

	LOG_FATAL("Just testing to see if ill get %f", 3.14f);
	LOG_INFO("WOOWW %s %.2f", "Now everything works and i can print PI: ", 3.14f);
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