#pragma once
#include "Core.h"
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>

extern "C" struct BALKAN3D_API Vertex
{
	glm::vec3 position;
	glm::vec3 color;
};

extern "C" class BALKAN3D_API Mesh
{
public:
	Mesh();
	~Mesh();

	void use();
	void draw();

	void submit();

public:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
private:
	GLuint VAO = 0;
	GLuint VBO = 0;
	GLuint EBO = 0;
};