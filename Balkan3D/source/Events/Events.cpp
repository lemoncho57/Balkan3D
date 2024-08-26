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
	
	if (glfwGetKey((GLFWwindow*)m_window, key) == GLFW_PRESS)
		pressed = true;
	
	return pressed;
}

bool Events::isKeyReleased(enum KeyCodes::Keys key)
{
	bool released = false;

	if (glfwGetKey((GLFWwindow*)m_window, key) == GLFW_RELEASE)
		released = true;

	return released;
}

bool Events::isMouseKeyReleased(enum KeyCodes::MouseKeys key)
{
	bool pressed = false;
	if (glfwGetMouseButton((GLFWwindow*)m_window, key) == GLFW_PRESS)
		pressed = true;

	return pressed;
}

void Events::getMouseCursorPosition(double* x, double* y)
{
	glfwGetCursorPos((GLFWwindow*)m_window, x, y);
}

bool Events::isMouseKeyPressed(enum KeyCodes::MouseKeys key)
{
	bool released = false;
	if (glfwGetMouseButton((GLFWwindow*)m_window, key) == GLFW_RELEASE)
		released = true;

	return released;
}
