#include "pch.h"
#include "Graphics/Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Logging/Loging.h"

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

void processMesh(aiMesh* mesh, const aiScene* scene, std::vector<Vertex>* vertices, std::vector<GLuint>* indices)
{
	for (size_t i = 0; i < mesh->mNumVertices; ++i)
	{
		aiVector3D pos = mesh->mVertices[i];
		Vertex v = {
			.position = {pos.x, pos.y, pos.z},
			.color = {1.f,1.f,1.f,1.f}
		};

		if (mesh->HasNormals())
		{
			aiVector3D normals = mesh->mNormals[i];
			v.normal = {normals.x, normals.y, normals.z};		
		}
		
		if (mesh->mTextureCoords[0])
		{
			aiVector3D texCoords = mesh->mTextureCoords[0][i];
			v.texCoords = {texCoords.x, texCoords.y};
		}
		
		vertices->push_back(v);
	}
	
	for (size_t i = 0; i < mesh->mNumFaces; ++i)
	{
		aiFace face = mesh->mFaces[i];
		for (size_t j = 0; j < face.mNumIndices; ++j)
			indices->push_back((GLuint) face.mIndices[j]);
		
	}
}

void processNode(aiNode* node, const aiScene* scene, std::vector<Vertex>* vertices, std::vector<GLuint>* indices)
{
	for (size_t i = 0; i < node->mNumMeshes; ++i)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		processMesh(mesh, scene, vertices, indices);
	}	
	
	for (size_t i = 0; i < node->mNumChildren; ++i)
		processNode(node->mChildren[i], scene, vertices, indices);	
}

Mesh::Mesh(const char* path, glm::vec3 transform, glm::vec3 rotation, glm::vec3 scale)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	m_modelMatrix = glm::mat4(1.f);

	m_transform = transform;
	m_rotation = rotation;
	m_scale = scale;

	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		LOG_ERROR("Unable to open model, error message: %s", importer.GetErrorString());
		return;
	}
	
	processNode(scene->mRootNode, scene, &this->vertices, &this->indices);

	update();	
	submit();
}

Mesh::~Mesh()
{
	glBindVertexArray(VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
}

void Mesh::draw()
{
	glBindVertexArray(VAO);
	if (!indices.empty())
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, vertices.data()->position[0], vertices.size());
	
	glBindVertexArray(0);
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

	// TexCoords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));
	glEnableVertexAttribArray(2);

	// Normals
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),(GLvoid*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);
}

const glm::mat4& Mesh::getModelMatrix()
{
	return m_modelMatrix;
}

Mesh* Mesh::Plane(glm::vec3 transform, glm::vec3 rotation, glm::vec3 scale, glm::vec4 color)
{
	Mesh* mesh = new Mesh(transform, rotation, scale);

	mesh->vertices =
	{
		{{-0.5f, 0.5f, 0.f}, color, {0.f, 1.f}, {0.f,0.f,1.f}},
		{{-0.5f,-0.5f,0.f},	color, {0.f, 0.f}, {0.f,0.f,1.f}},
		{{0.5f,-0.5f,0.f},	color, {1.f, 0.f}, {0.f,0.f,1.f}},
		{{0.5f,0.5f,0.f},	color, {1.f, 1.f}, {0.f,0.f,1.f}}
	};
	mesh->indices = 
	{
		0,1,2,
		0,2,3
	};

	mesh->submit();

	return mesh;
}

Mesh* Mesh::Cube(glm::vec3 transform, glm::vec3 rotation, glm::vec3 scale, glm::vec4 color)
{
	Mesh* mesh = new Mesh(transform, rotation, scale);

	// mesh->vertices =
	// {
	// 	{{-0.5f, 0.5f, 0.5f}, color, {0.f, 1.f}, {0.f, 0.f, 1.f}},	//0 Front up left
	// 	{{-0.5f,-0.5f,0.5f}, color, {0.f, 0.f}, {0.f, 0.f, 1.f}},	//1 Front down left
	// 	{{0.5f,-0.5f,0.5f},	color, {1.f, 0.f},	{0.f, 0.f, 1.f}},	//2 Front down right
	// 	{{0.5f,0.5f,0.5f},	color, {1.f, 1.f},	{0.f, 0.f, 1.f}},	//3 Front up right

	// 	{{-0.5f, 0.5f, -0.5f}, color, {0.f, 1.f},{0.f, 0.f, -1.f}},	 //4 Back up left
	// 	{{-0.5f, -0.5f, -0.5f}, color, {0.f, 0.f},	{0.f, 0.f, -1.f}},//5 Back down left
	// 	{{0.5, -0.5f, -0.5f}, color, {1.f, 0.f}, {0.f, 0.f, -1.f}},	 //6 Back down right
	// 	{{0.5f,0.5f,-0.5f},	color, {1.f, 1.f},	{0.f, 0.f, -1.f}}	 //7 Back up right
	// };

	// mesh->indices =
	// {
	// 	0,1,2, // Front
	// 	0,2,3,

	// 	0,1,5, // Left
	// 	0,5,4,

	// 	4,5,6, // Back
	// 	4,6,7,

	// 	3,2,6, // Right
	// 	3,6,7,

	// 	0,3,4, // Up
	// 	4,3,7,

	// 	1,2,5,
	// 	5,2,6
	// };

	mesh->vertices = 
	{
		{{-1.0f, -1.0f,  1.0f}, color,  {0.f,0.f},{0.0f, 0.0f, 1.0f}},  // Bottom-left
     	{{1.0f, -1.0f,  1.0f},  color , {1.f,0.f},{0.0f, 0.0f, 1.0f}},  // Bottom-right
     	{{1.0f,  1.0f,  1.0f},  color , {1.f,1.f},{0.0f, 0.0f, 1.0f}},  // Top-right
    	{{-1.0f,  1.0f,  1.0f}, color , {0.f,1.f}, {0.0f, 0.0f, 1.0f}},  // Top-left}
		
    	{{-1.0f, -1.0f, -1.0f}, color ,{0.0f, 0.0f},  {0.0f,  0.0f, -1.0f}},  // Back-bottom-left
    	{{ 1.0f, -1.0f, -1.0f}, color ,{1.0f, 0.0f},  {0.0f,  0.0f, -1.0f}},  // Back-bottom-right
    	{{ 1.0f,  1.0f, -1.0f}, color ,{1.0f, 1.0f},  {0.0f,  0.0f, -1.0f}},  // Back-top-right
    	{{-1.0f,  1.0f, -1.0f}, color ,{0.0f, 1.0f},  {0.0f,  0.0f, -1.0f}},  // Back-top-left
		
		{{-1.0f,  1.0f,  1.0f}, color, {0.0f, 0.0f},  {0.0f,  1.0f,  0.0f}},  // Top-bottom-left
     	{{1.0f,  1.0f,  1.0f},  color, {1.0f, 0.0f},  {0.0f,  1.0f,  0.0f}},  // Top-bottom-right
     	{{1.0f,  1.0f, -1.0f},  color, {1.0f, 1.0f},  {0.0f,  1.0f,  0.0f}},  // Top-top-right
    	{{-1.0f,  1.0f, -1.0f},  color, {0.0f, 1.0f},  {0.0f,  1.0f,  0.0f}},  // Top-top-left
	
		{{-1.0f, -1.0f,  1.0f},  color, {0.0f, 0.0f},  {0.0f, -1.0f,  0.0f}},  // Bottom-bottom-left
    	{{ 1.0f, -1.0f,  1.0f},  color, {1.0f, 0.0f},  {0.0f, -1.0f,  0.0f}},  // Bottom-bottom-right
    	{{ 1.0f, -1.0f, -1.0f},  color, {1.0f, 1.0f},  {0.0f, -1.0f,  0.0f}},  // Bottom-top-right
    	{{-1.0f, -1.0f, -1.0f},  color, {0.0f, 1.0f},  {0.0f, -1.0f,  0.0f}},  // Bottom-top-left

		{{1.0f, -1.0f,  1.0f}, color ,{0.0f, 0.0f},  {1.0f,  0.0f,  0.0f}},  // Right-bottom-left
     	{{1.0f,  1.0f,  1.0f}, color ,{1.0f, 0.0f},  {1.0f,  0.0f,  0.0f}},  // Right-bottom-right
     	{{1.0f,  1.0f, -1.0f}, color ,{1.0f, 1.0f},  {1.0f,  0.0f,  0.0f}},  // Right-top-right
     	{{1.0f, -1.0f, -1.0f}, color ,{0.0f, 1.0f},  {1.0f,  0.0f,  0.0f}},  // Right-top-left

		{{-1.0f, -1.0f,  1.0f}, color, {0.0f, 0.0f}, {-1.0f,  0.0f,  0.0f}},  // Left-bottom-left
    	{{-1.0f,  1.0f,  1.0f}, color, {1.0f, 0.0f}, {-1.0f,  0.0f,  0.0f}},  // Left-bottom-right
    	{{-1.0f,  1.0f, -1.0f}, color, {1.0f, 1.0f}, {-1.0f,  0.0f,  0.0f}},  // Left-top-right
    	{{-1.0f, -1.0f, -1.0f}, color, {0.0f, 1.0f}, {-1.0f,  0.0f,  0.0f}}   // Left-top-left
	};

	mesh->indices =
	{
		// Front face
    	0, 1, 2,
		2, 3, 0,

    	// Back face
    	4, 5, 6,
		6, 7, 4,

    	// Top face
    	8, 9, 10,
		10, 11, 8,

    	// Bottom face
    	12, 13, 14,
		14, 15, 12,

    	// Right face
    	16, 17, 18,
		18, 19, 16,

    	// Left face
    	20, 21, 22,
		22, 23, 20
	};

	mesh->submit();
	return mesh;
}

void Mesh::setPosition(glm::vec3 transform)
{
	m_transform = transform;
	update();
}

void Mesh::setRotation(glm::vec3 rotation)
{
	m_rotation = rotation;
	update();
}

void Mesh::setScale(glm::vec3 scale)
{
	m_scale = scale;
	update();
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