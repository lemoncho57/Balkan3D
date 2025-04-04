#include <Balkan3D/include/Window.h>
#include <Balkan3D/include/Logging/Loging.h>
#include <Balkan3D/include/Events/Events.h>
#include <Balkan3D/include/Logging/Asserts.h>
#include <Balkan3D/include/Graphics/GraphicsUtils.h>
#include <Balkan3D/include/Graphics/Shader.h>
#include <Balkan3D/include/Graphics/Mesh.h>
#include <Balkan3D/include/Graphics/Texture.h>
#include <Balkan3D/include/Graphics/Camera.h>
#include <Balkan3D/include/Time/Clock.h>
#include <Balkan3D/include/Graphics/Light.h>
#include <Balkan3D/include/Graphics/Material.h>
#include <Balkan3D/include/Graphics/Framebuffer.h>
#include <string>

// Code is just for testing
int main(void)
{
	Window window("Idk", 1280, 720);
	Events events;
	
	Shader shader((const char*)"vertex.glsl", (const char*)"fragment.glsl");
	shader.setName("Default");
	
	Camera camera(glm::vec3(0.f, 0.f, 3.f), 50.f, (float) window.getWidth() / (float) window.getHeight());
	
	//Mesh bmw("bmwe34/source/BMW M5 E34.obj", &shader);
	Mesh& mesh = *Mesh::Cube();
	Mesh& mesh2 = *Mesh::Plane();
	
	mesh.setShader(&shader);
	mesh2.setShader(&shader);
	
	Framebuffer framebuffer(window.getWidth(), window.getHeight());
	//Texture texture("Ne_e_shoferska.png");
	Texture texture2("Bira.png");

	Material mat(1.f);

	Light light;
	light.pos = {-2.78f,0.f,-2.3f};
	light.color = {1.f,1.f,1.f};

	events.setCurrentWindow(&window);
	shader.use();
	shader.setvec3f("userColor", { 1.f,1.f,1.f });
	shader.unuse();
	mesh2.setPosition({0,0,-3});
	//bmw.setPosition({0.f, 0.f, -2.f});

	int fps = 165.f;
	while(!window.shouldClose())
	{
		window.beginDrawing(fps, &framebuffer);
		framebuffer.bind();
		GraphicsUtils::clearColor(0.f, 0.f, 0.f, 1.f);

		//texture2.use();
		mesh.draw();
		mesh2.draw();
		//texture2.unuse();
		framebuffer.unbind();

		{
			static float speed = 1.5f;
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
				camera.move(CAMERA_DIRECTION_FRONT, speed);
			if (events.isKeyPressed(KeyCodes::KEY_S))
				camera.move(CAMERA_DIRECTION_BACK, speed);
			if (events.isKeyPressed(KeyCodes::KEY_A))
				camera.move(CAMERA_DIRECTION_LEFT, speed);
			if (events.isKeyPressed(KeyCodes::KEY_D))
				camera.move(CAMERA_DIRECTION_RIGHT, speed);
			if (events.isKeyPressed(KeyCodes::KEY_SPACE))
				camera.move(CAMERA_DIRECTION_UP, speed);
			if (events.isKeyPressed(KeyCodes::KEY_LEFT_CONTROL))
				camera.move(CAMERA_DIRECTION_DOWN, speed);
			if (events.isKeyPressed(KeyCodes::KEY_LEFT_SHIFT))
				speed = 5.f;

			else if(events.isKeyReleased(KeyCodes::KEY_LEFT_SHIFT))
				speed = 1.5f;
			
			if (events.isKeyPressed(KeyCodes::KEY_RIGHT))
				camera.setYaw(camera.getYaw() + 70.f * Clock::getDeltaTime());
			if (events.isKeyPressed(KeyCodes::KEY_LEFT))
				camera.setYaw(camera.getYaw() - 70.f * Clock::getDeltaTime());
			if (events.isKeyPressed(KeyCodes::KEY_DOWN))
				camera.setPitch(camera.getPitch() - 70.f * Clock::getDeltaTime());
			if (events.isKeyPressed(KeyCodes::KEY_UP))
				camera.setPitch(camera.getPitch() + 70.f * Clock::getDeltaTime());
			if (events.isKeyPressed(KeyCodes::KEY_R))
				camera.setPosition({ 0.f,0.f,0.f });

			if (events.isKeyPressed(KeyCodes::KEY_KP_ADD))
				fps += 1.f;
			else if (events.isKeyPressed(KeyCodes::KEY_KP_SUBTRACT))
				fps -= 1.f;

			if (events.isKeyPressed(KeyCodes::KEY_T))
				camera.setPosition(light.pos);
			else
				camera.setPosition(camera.getPosition());

			static bool wireframe = false;
			// if (events.isKeyPressed(KeyCodes::KEY_L))
			// 	wireframe = true;
			// else
			// 	wireframe = false;
			// if(wireframe)
			// 	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			// else
			// 	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			//if (events.isKeyPressed(KeyCodes::KEY_UP))
			//	mesh.setPosition({ mesh.getPosition().x, mesh.getPosition().y + 0.03f, mesh.getPosition().z }); // Needs to be multiplied by delta
			//else
			//	mesh.setPosition(mesh.getPosition());
		};
		//glClear(GL_COLOR_BUFFER_BIT);

		shader.use();
		shader.set1i("tex", 0);
		shader.setmat4fv("camMatrix", camera.getViewMatrix(), 0);
		shader.setmat4fv("projMatrix", camera.getProjectionMatrix(), 0);
		shader.setvec3f("lightPos", light.pos);
		shader.setvec3f("lightColor", light.color);
		shader.setvec3f("camPos", camera.getPosition());

		shader.setvec3f("material.diffuse", mat.diffuse);
		shader.setvec3f("material.specular", mat.specular);
		shader.set1f("material.shininess", mat.shininess);

		texture2.use();

		// texture.activateTexture(0x84C0);
		//texture.use();
		//bmw.draw();
		//texture.unuse();
		// texture2.activateTexture(0x84C1);
		// texture2.use();
		texture2.unuse();

		if (events.isKeyPressed(KeyCodes::KEY_ESCAPE))
			window.close();

		shader.unuse();
		window.endDrawing();
	}

	window.release();
	return 0;
}
