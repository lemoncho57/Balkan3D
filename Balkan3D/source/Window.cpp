#include "pch.h"
#include "Window.h"

Window::Window(const char* title, int width, int height)
	: m_title((char*)title), m_width(width), m_height(height)
{
	BALKAN3D_ASSERT(glfwInit(), "Unable to initialize GLFW!");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	m_window = glfwCreateWindow(width, height, title, NULL, NULL);
	BALKAN3D_ASSERT(m_window, "Unable to create window");

	glfwMakeContextCurrent((GLFWwindow*)m_window);

	BALKAN3D_ASSERT(gladLoadGL(), "Unable to load OpenGL");
	BALKAN3D_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Unable to initialize glad");

	glEnable(GL_DEPTH_TEST);
}

Window::~Window()
{
	close();
}

void Window::beginDrawing()
{
	glfwGetFramebufferSize((GLFWwindow*)m_window, &m_width, &m_height);
	glViewport(0, 0, m_width, m_height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::endDrawing()
{
	glfwSwapBuffers((GLFWwindow*)m_window);
	glfwPollEvents();
}

void Window::close()
{
	glfwSetWindowShouldClose((GLFWwindow*)m_window, GLFW_TRUE);
}

void Window::swapBuffers()
{
	glfwSwapBuffers((GLFWwindow*)m_window);
}

void Window::release()
{
	glfwDestroyWindow((GLFWwindow*)m_window);
	glfwTerminate();
}

void* Window::getWindow() const
{
	return m_window;
}

int Window::getWidth() const
{
	return m_width;
}

int Window::getHeight() const
{
	return m_height;
}

void Window::setSize(int width, int height)
{
	glfwSetWindowSize((GLFWwindow*)m_window, width, height);
}

bool Window::shouldClose() const
{
	return glfwWindowShouldClose((GLFWwindow*)m_window);
}