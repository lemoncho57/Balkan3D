#include <Balkan3D/include/Logging/Loging.h>
#include <Balkan3D/include/Window.h>
#include <Balkan3D/include/Logging/Asserts.h>
#include <Balkan3D/include/Graphics/GraphicsUtils.h>
#include <Balkan3D/include/Graphics/Shader.h>
#include <Balkan3D/include/Graphics/Mesh.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

// Code is just for testing
int main(void)
{
	Window window("Idk", 1280, 720);
	Events events;

	Shader shader(/*Vertex Shader*/ R"(
					#version 410 core
					layout (location = 0) in vec3 aPos;
					layout (location = 1) in vec3 aColor;
					
					out vec3 color;
					
					void main()
					{
						gl_Position = vec4(aPos, 1.0);
						color = aColor;
					})",
					/*Fragment*/R"(
					#version 410 core
					out vec4 fragColor;
					
					in vec3 color;
					
					uniform vec3 userColor;

					void main()
					{
						fragColor = vec4(userColor, 1.0);
					}
					)");
	Mesh mesh;
	mesh.vertices = 
	{
		{{-0.5f, 0.5f, 0.f}, {0.f,0.f,1.f}},
		{{-0.5f,-0.5f,0.f},	{0.f,0.f,1.f}},
		{{0.5f,-0.5f,0.f},	{0.f,0.f,1.f}},
		{{0.5f,0.5f,0.f},	{0.f,0.f,1.f}}
	};

	mesh.indices =
	{
		0,1,2,
		0,2,3
	};

	events.setCurrentWindow(&window);

	while(!window.shouldClose())
	{
		window.beginDrawing();
		GraphicsUtils::clearColor(1.f, 1.f, 0.f, 1.f);

		if (events.isKeyPressed(KeyCodes::KEY_KP_1))
			shader.setvec3f("userColor", { 1.f,0.f,0.f });
		else if (events.isKeyPressed(KeyCodes::KEY_KP_2))
			shader.setvec3f("userColor", { 0.f,1.f,0.f });
		else if (events.isKeyPressed(KeyCodes::KEY_KP_3))
			shader.setvec3f("userColor", { 0.f,0.f,1.f });
		else if (events.isKeyPressed(KeyCodes::KEY_KP_0))
			shader.setvec3f("userColor", { 0.f,0.f,0.f });

		shader.use();
		
		mesh.submit();
		mesh.draw();

		if (events.isKeyPressed(KeyCodes::KEY_ESCAPE))
			window.close();

		shader.unuse();
		window.endDrawing();
	}

	window.release();
	return 0;
}