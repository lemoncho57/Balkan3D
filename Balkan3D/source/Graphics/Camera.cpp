#include "pch.h"
#include "Graphics/Camera.h"

Camera::Camera(glm::vec3 position, float fov, float aspect, float near, float far)
	: m_viewMatrix(1.f), m_projMatrix(1.f), m_pos(position), m_cameraFront(0.f, 0.f, -1.f), m_fov(fov),
	m_near(near), m_far(far), m_aspect(aspect), m_yaw(-90.f), m_pitch(0.f)
{
	update();
}

Camera::~Camera()
{

}

const glm::mat4& Camera::getViewMatrix()
{
	update();
	m_viewMatrix = glm::lookAt(m_pos,m_pos + m_cameraFront, m_cameraUp);
	return m_viewMatrix;
}

const glm::mat4& Camera::getProjectionMatrix()
{
	m_projMatrix = glm::perspective(glm::radians(m_fov), m_aspect, m_near, m_far);
	return m_projMatrix;
}

void Camera::setPosition(const glm::vec3& pos)
{

}

glm::vec3 Camera::getPosition() const
{
	return m_pos;
}


float Camera::getFov() const
{
	return m_fov;
}

void Camera::move()
{

}

void Camera::update()
{
	glm::vec3 front;
	front.x = glm::cos(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch));
	front.y = glm::sin(glm::radians(m_pitch));
	front.z = glm::sin(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch));
	m_cameraFront = glm::normalize(front);

	m_cameraRight = glm::normalize(glm::cross(m_cameraFront, m_worldUp));
	m_cameraUp = glm::normalize(glm::cross(m_cameraRight, m_cameraFront));
}
