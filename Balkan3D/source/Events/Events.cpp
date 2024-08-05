#include "pch.h"
#include "Events/Events.h"

Events::Events()
{
}

Events::~Events()
{
}

void Events::setCurrentWindow(Window* window)
{
	m_window = window->getWindow();
}

bool Events::isKeyPressed(enum KeyCodes::Keys key)
{
	bool pressed = false;
	
	if (glfwGetKey(m_window, key) == GLFW_PRESS)
		pressed = true;
	
	return pressed;
}

bool Events::isKeyReleased(enum KeyCodes::Keys key)
{
	bool released = false;

	if (glfwGetKey(m_window, key) == GLFW_RELEASE)
		released = true;

	return released;
}
