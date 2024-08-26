#ifndef WINDOW_H
#define WINDOW_H
#include "Time/Clock.h"

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

	void* getWindow() const;
	int getWidth() const;
	int getHeight() const;
	void setSize(int width, int height);
	bool shouldClose() const;


private:
	char* m_title;
	int m_width;
	int m_height;
	void* m_window;
};
#endif //WINDOW_H