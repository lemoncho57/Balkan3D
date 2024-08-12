#include "pch.h"
#include "Graphics/Mesh.h"

Mesh::Mesh(glm::vec3 transform, glm::vec3 rotation, glm::vec3 scale)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	m_modelMatrix = glm::mat4(1.f);

	m_transform = transform;
	m_rotation = rotation;
	m_scale = scale;

	update();
	submit();
}

//Mesh::Mesh(glm::vec3 transform /*= glm::vec3(0.f, 0.f, 0.f)*/, glm::vec3 rotation /*= glm::vec3(0.f, 0.f, 0.f)*/, glm::vec3 scale /*= glm::vec3(1.f, 1.f, 1.f)*/)
//{
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &EBO);
//
//	m_modelMatrix = glm::mat4(1.f);
//
//	m_transform = transform;
//	m_rotation = rotation;
//	m_scale = scale;
//
//	update();
//	submit();
//}

Mesh::~Mesh()
{
	glBindVertexArray(VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
}

void Mesh::draw()
{
	update();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::submit()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	if (vertices.size() > 0)
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	else
		glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_STATIC_DRAW);
	

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	if (indices.size() > 0)
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
	else
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, NULL, GL_STATIC_DRAW);

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	// Color
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

const glm::mat4& Mesh::getModelMatrix()
{
	update();
	return m_modelMatrix;
}

void Mesh::setPosition(glm::vec3 transform)
{
	m_transform = transform;
}

void Mesh::setRotation(glm::vec3 rotation)
{
	m_rotation = rotation;
}

void Mesh::setScale(glm::vec3 scale)
{
	m_scale = scale;
}

glm::vec3 Mesh::getPosition() const
{
	return glm::vec3();
}

glm::vec3 Mesh::getRotation() const
{
	return glm::vec3();
}

glm::vec3 Mesh::getScale() const
{
	return glm::vec3();
}

void Mesh::update()
{
	m_modelMatrix = glm::translate(m_modelMatrix, m_transform);
	m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_rotation.x), glm::vec3(1.f, 0.f, 0.f));
	m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_rotation.y), glm::vec3(0.f, 1.f, 0.f));
	m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_rotation.z), glm::vec3(0.f, 0.f, 1.f));
	m_modelMatrix = glm::scale(m_modelMatrix, m_scale);
}
