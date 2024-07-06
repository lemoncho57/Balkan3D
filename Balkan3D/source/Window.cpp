#include <pch.h>
#include "Window.h"
#include <assert.h>

Window::Window(const char* title, int width, int height)
	: m_title((char*) title), m_width(width), m_height(height)
{
	
}

Window::~Window()
{

}

extern "C" BALKAN3D_API bool Window::initSDL(Uint32 flags)
{
	if (SDL_Init(flags) < 0)
	{
		//LOG_ERROR("Unable to initialize SDL!");
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	m_window = SDL_CreateWindow(m_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_OPENGL);

	m_glContext = SDL_GL_CreateContext(m_window);
	if (!m_glContext)
	{
		//LOG_ERROR("Unable to initialize OpenGL!");
		return false;
	}

	return true;
}

extern "C" BALKAN3D_API void Window::release()
{
	SDL_DestroyWindow(m_window);
	SDL_GL_DeleteContext(m_glContext);
	SDL_Quit();
}

extern "C" BALKAN3D_API SDL_Window* Window::getWindow() const
{
	return m_window;
}

extern "C" BALKAN3D_API int Window::getWindowWidth() const
{
	return m_width;
}

extern "C" BALKAN3D_API int Window::getWindowHeight() const
{
	return m_height;
}