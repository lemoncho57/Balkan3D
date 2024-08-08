#pragma once

#include "Core.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

extern "C" class BALKAN3D_API Camera
{
public:
	Camera(glm::vec3 position, float fov = 80, float aspect = 1.f, float near = 0.1f, float far = 100.f);
	~Camera();

	const glm::mat4& getViewMatrix();
	const glm::mat4& getProjectionMatrix();
		
	void setPosition(const glm::vec3& pos);
	glm::vec3 getPosition() const;

	float getFov() const;

	void move();

private:
	void update();
	
private:
	
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projMatrix;
	glm::vec3 m_pos;

	glm::vec3 m_cameraRight;
	glm::vec3 m_cameraFront;
	glm::vec3 m_cameraUp;

	glm::vec3 m_worldUp = glm::vec3(0.f,1.f,0.f);

	float m_yaw;
	float m_pitch;

	float m_fov;
	GLfloat m_near;
	GLfloat m_far;
	float m_aspect;
};