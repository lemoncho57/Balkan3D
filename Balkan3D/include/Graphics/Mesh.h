#ifndef GRAPHICS_MESH_H
#define GRAPHICS_MESH_H
#include "../Defines.h"
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <vector>

extern "C" struct BALKAN3D_API Vertex
{
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 texCoords;
	glm::vec3 normal;
};

extern "C" struct BALKAN3D_API Face
{
	std::vector<unsigned int> vertexInd;
	std::vector<unsigned int> normalInd;
	std::vector<unsigned int> texCoordInd;
};

extern "C" class BALKAN3D_API Mesh
{
public:
	Mesh(glm::vec3 transform = glm::vec3(0.f, 0.f, 0.f), glm::vec3 rotation = glm::vec3(0.f, 0.f, 0.f), glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f));
	Mesh(const char* path, glm::vec3 transform = glm::vec3(0.f, 0.f, 0.f), glm::vec3 rotation = glm::vec3(0.f, 0.f, 0.f), glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f));
	~Mesh();

	//void use(); // This is already done in draw
	void draw(); 

	void submit();

	const glm::mat4& getModelMatrix();

	static Mesh* Plane(glm::vec3 transform = glm::vec3(0.f, 0.f, 0.f), glm::vec3 rotation = glm::vec3(0.f, 0.f, 0.f), glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f), glm::vec4 color = glm::vec4(1.f,1.f,1.f,1.f));
	// TODO: Fix cube texture
	static Mesh* Cube(glm::vec3 transform = glm::vec3(0.f, 0.f, 0.f), glm::vec3 rotation = glm::vec3(0.f, 0.f, 0.f), glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f), glm::vec4 color = glm::vec4(1.f,1.f,1.f,1.f));

	void setPosition(glm::vec3 transform);
	void setRotation(glm::vec3 rotation);
	void setScale(glm::vec3 scale);
	glm::vec3 getPosition() const;
	glm::vec3 getRotation() const;
	glm::vec3 getScale() const;

private:
	void update();
	bool loadObj(const char* file, std::vector<Vertex> &outVertices, std::vector<Face> &outFaces);

public:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Face> faces;
private:
	GLuint VAO = 0;
	GLuint VBO = 0;
	GLuint EBO = 0;

	glm::mat4 m_modelMatrix;
	glm::vec3 m_transform;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;

};
#endif //GRAPHICS_MESH_H