#ifndef EVENTS_EVENTS_H
#define EVENTS_EVENTS_H
#include "pch.h"

enum Keys;

extern "C" class BALKAN3D_API Events
{
public:
	Events();
	~Events();

	void setCurrentWindow(Window* window);

	bool isKeyPressed(enum KeyCodes::Keys key);
	bool isKeyReleased(enum KeyCodes::Keys key);

	bool isMouseKeyPressed(enum KeyCodes::MouseKeys key);
	bool isMouseKeyReleased(enum KeyCodes::MouseKeys key);

	void getMouseCursorPosition(double* x, double* y);
private:
	GLFWwindow* m_window;
};
#endif //EVENTS_EVENTS_H