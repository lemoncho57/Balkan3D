#include <Balkan3D/include/Logging/Loging.h>
#include <Balkan3D/include/Window.h>
#include <Balkan3D/include/Logging/Asserts.h>
#include <Balkan3D/include/Graphics/GraphicsUtils.h>
#include <Balkan3D/include/Graphics/Shader.h>
#include <Balkan3D/include/Graphics/Mesh.h>
#include <Balkan3D/include/Graphics/Texture.h>
#include <Balkan3D/include/Graphics/Camera.h>
#include <Balkan3D/include/Time/Clock.h>
#include <string>

// Code is just for testing
int main(void)
{
	Window window("Idk", 1280, 720);
	Events events;

	Shader shader(/*Vertex Shader*/ R"(
					#version 410 core
					layout (location = 0) in vec3 aPos;
					layout (location = 1) in vec4 aColor;
					layout (location = 2) in vec2 aTexCoords;

					out vec4 color;
					out vec2 texCoords;

					uniform mat4 camMatrix;
					uniform mat4 projMatrix;
					uniform mat4 modelMatrix;

					void main()
					{
						gl_Position = projMatrix * camMatrix * modelMatrix * vec4(aPos, 1.0);
						color = aColor;
						texCoords = aTexCoords;
					})",
					/*Fragment*/R"(
					#version 410 core
					out vec4 fragColor;
					
					in vec4 color;
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

	Mesh& mesh = *Mesh::Cube(); // the textures are not correct
	//mesh.setPosition({ 0.f, 1.f,0.f });
	//mesh.vertices = 
	//{
	//	{{-0.5f, 0.5f, 0.f}, {0.f,0.f,1.f, 1.f}, {0.f, 1.f}},
	//	{{-0.5f,-0.5f,0.f},	{0.f,0.f,1.f, 1.f}, {0.f, 0.f}},
	//	{{0.5f,-0.5f,0.f},	{0.f,0.f,1.f, 1.f}, {1.f, 0.f}},
	//	{{0.5f,0.5f,0.f},	{0.f,0.f,1.f, 1.f}, {1.f, 1.f}}
	//};

	//mesh.indices =
	//{
	//	0,1,2,
	//	0,2,3
	//};

	Texture texture("Ne_e_shoferska.png");
	Texture texture2("Bira.png");

	events.setCurrentWindow(&window);
	shader.use();
	shader.setvec3f("userColor", { 1.f,1.f,1.f });
	shader.unuse();

	int fps = 30.f;
	while(!window.shouldClose())
	{
		window.beginDrawing(fps);
		GraphicsUtils::clearColor(1.f, 1.f, 0.f, 1.f);

		{
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

			if (events.isKeyPressed(KeyCodes::KEY_W))
				camera.move(CAMERA_DIRECTION_FRONT);
			if (events.isKeyPressed(KeyCodes::KEY_S))
				camera.move(CAMERA_DIRECTION_BACK);
			if (events.isKeyPressed(KeyCodes::KEY_A))
				camera.move(CAMERA_DIRECTION_LEFT);
			if (events.isKeyPressed(KeyCodes::KEY_D))
				camera.move(CAMERA_DIRECTION_RIGHT);
			if (events.isKeyPressed(KeyCodes::KEY_SPACE))
				camera.move(CAMERA_DIRECTION_UP);
			if (events.isKeyPressed(KeyCodes::KEY_LEFT_CONTROL))
				camera.move(CAMERA_DIRECTION_DOWN);

			if (events.isKeyPressed(KeyCodes::KEY_RIGHT))
				camera.setYaw(camera.getYaw() + 35.f * Clock::getDeltaTime());
			if (events.isKeyPressed(KeyCodes::KEY_LEFT))
				camera.setYaw(camera.getYaw() - 35.f * Clock::getDeltaTime());
			if (events.isKeyPressed(KeyCodes::KEY_DOWN))
				camera.setPitch(camera.getPitch() - 35.f * Clock::getDeltaTime());
			if (events.isKeyPressed(KeyCodes::KEY_UP))
				camera.setPitch(camera.getPitch() + 35.f * Clock::getDeltaTime());
			if (events.isKeyPressed(KeyCodes::KEY_R))
				camera.setPosition({ 0.f,0.f,0.f });

			if (events.isKeyPressed(KeyCodes::KEY_KP_ADD))
				fps += 1.f;
			else if (events.isKeyPressed(KeyCodes::KEY_KP_SUBTRACT))
				fps -= 1.f;
			//if (events.isKeyPressed(KeyCodes::KEY_UP))
			//	mesh.setPosition({ mesh.getPosition().x, mesh.getPosition().y + 0.03f, mesh.getPosition().z }); // Needs to be multiplied by delta
			//else
			//	mesh.setPosition(mesh.getPosition());
		};

		shader.use();
		shader.set1i("tex", 0);
		shader.set1i("tex2", 1);
		shader.setmat4fv("camMatrix", camera.getViewMatrix(), GL_FALSE);
		shader.setmat4fv("projMatrix", camera.getProjectionMatrix(), GL_FALSE);
		shader.setmat4fv("modelMatrix", mesh.getModelMatrix(), GL_FALSE);
		
		texture.activateTexture(GL_TEXTURE0);
		texture.use();
		texture2.activateTexture(GL_TEXTURE1);
		texture2.use();
		mesh.draw();

		if (events.isKeyPressed(KeyCodes::KEY_ESCAPE))
			window.close();

		texture.unuse();
		texture2.unuse();
		shader.unuse();
		window.endDrawing();
	}

	window.release();
	return 0;
}