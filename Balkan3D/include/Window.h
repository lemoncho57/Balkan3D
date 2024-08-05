#pragma once
#include "pch.h"

extern "C" class BALKAN3D_API Window
{
public:
	Window(const char* title, int width, int height);
	~Window();

	void beginDrawing();
	void endDrawing();

	void close();
	void release();

	void swapBuffers();

	GLFWwindow* getWindow() const;
	int getWidth() const;
	int getHeight() const;
	void setSize(int width, int height);
	bool shouldClose() const;

private:
	char* m_title;
	int m_width;
	int m_height;
	GLFWwindow* m_window;
};