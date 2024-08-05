#pragma once
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
private:
	GLFWwindow* m_window;
};