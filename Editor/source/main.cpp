#include <Balkan3D/include/Logging/Loging.h>
#include <Balkan3D/include/Window.h>
#include <Balkan3D/include/Logging/Asserts.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Code is just for testing
int main(void)
{
	Window window("Idk", 1280, 720);
	Events events;

	events.setCurrentWindow(&window);

	while(!window.shouldClose())
	{
		window.beginDrawing();

		if (events.isKeyPressed(KeyCodes::KEY_ESCAPE))
			window.close();

		window.endDrawing();
	}

	window.release();
	return 0;
}