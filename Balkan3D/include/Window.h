#pragma once

#include <SDL2/SDL.h>

extern "C" class BALKAN3D_API Window
{
public:
	Window(const char* title, int width, int height);
	~Window();

	bool initSDL(Uint32 flags = SDL_INIT_EVERYTHING);
	void release();

 	SDL_Window* getWindow() const;
	int getWindowWidth() const;
	int getWindowHeight() const;

private:
	char* m_title;
	int m_width;
	int m_height;
	SDL_Window* m_window = nullptr;
	SDL_GLContext m_glContext = nullptr;
};