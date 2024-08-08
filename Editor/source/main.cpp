#include <Balkan3D/include/Logging/Loging.h>
#include <Balkan3D/include/Window.h>
#include <Balkan3D/include/Logging/Asserts.h>
#include <Balkan3D/include/Graphics/GraphicsUtils.h>
#include <Balkan3D/include/Graphics/Shader.h>
#include <Balkan3D/include/Graphics/Mesh.h>
#include <Balkan3D/include/Graphics/Texture.h>
#include <Balkan3D/include/Graphics/Camera.h>
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
					layout (location = 2) in vec2 aTexCoords;					

					out vec3 color;
					out vec2 texCoords;					

					uniform mat4 camMatrix;
					uniform mat4 projMatrix;

					void main()
					{
						gl_Position = projMatrix * camMatrix * vec4(aPos, 1.0);
						color = aColor;
						texCoords = aTexCoords;
					})",
					/*Fragment*/R"(
					#version 410 core
					out vec4 fragColor;
					
					in vec3 color;
					in vec2 texCoords;
					
					uniform vec3 userColor;
					uniform sampler2D tex;
					uniform sampler2D tex2;
			
					void main()
					{
						fragColor = mix(texture(tex, texCoords), texture(tex2, texCoords), 0.4) * vec4(userColor, 1.0);
					}
					)");

	Camera camera(glm::vec3(0.f, 0.f, 3.f), 50.f,(float) window.getWidth() / (float) window.getHeight());

	Mesh mesh;
	mesh.vertices = 
	{
		{{-0.5f, 0.5f, 0.f}, {0.f,0.f,1.f}, {0.f, 1.f}},
		{{-0.5f,-0.5f,0.f},	{0.f,0.f,1.f}, {0.f, 0.f}},
		{{0.5f,-0.5f,0.f},	{0.f,0.f,1.f}, {1.f, 0.f}},
		{{0.5f,0.5f,0.f},	{0.f,0.f,1.f}, {1.f, 1.f}}
	};

	mesh.indices =
	{
		0,1,2,
		0,2,3
	};

	Texture texture("Ne_e_shoferska.png");
	Texture texture2("Bira.png");

	events.setCurrentWindow(&window);
	shader.setvec3f("userColor", { 1.f,1.f,1.f });

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
		else if (events.isKeyPressed(KeyCodes::KEY_KP_4))
			shader.setvec3f("userColor", { 1.f,1.f,1.f });
		else if (events.isKeyPressed(KeyCodes::KEY_KP_0))
			shader.setvec3f("userColor", { 0.f,0.f,0.f });

		shader.set1i("tex", 0);
		shader.set1i("tex2", 1);
		//shader.setmat4fv("projMatrix", camera.getProjectionMatrix(), GL_FALSE);
		glm::mat4 view = camera.getViewMatrix();
		shader.setmat4fv("camMatrix", view, GL_FALSE);
		glm::mat4 proj = camera.getProjectionMatrix();
		shader.setmat4fv("projMatrix", proj, GL_FALSE);
		shader.use();


		texture.activateTexture(GL_TEXTURE0);
		texture.bind();
		texture2.activateTexture(GL_TEXTURE1);
		texture2.bind();
		mesh.submit();
		mesh.draw();

		if (events.isKeyPressed(KeyCodes::KEY_ESCAPE))
			window.close();

		texture.unbind();
		texture2.unbind();
		shader.unuse();
		window.endDrawing();
	}

	window.release();
	return 0;
}