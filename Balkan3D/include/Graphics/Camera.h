#ifndef GRAPHICS_CAMERA_H
#define GRAPHICS_CAMERA_H

#include "../Defines.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#define CAMERA_DIRECTION_FRONT	0
#define CAMERA_DIRECTION_BACK	1
#define CAMERA_DIRECTION_LEFT	2
#define CAMERA_DIRECTION_RIGHT	3
#define CAMERA_DIRECTION_UP		4
#define CAMERA_DIRECTION_DOWN	5

extern "C" class BALKAN3D_API Camera
{
public:
	Camera(glm::vec3 position, float fov = 80, float aspect = 1.f, float near = 0.1f, float far = 100.f);
	~Camera();

	const glm::mat4& getViewMatrix();
	const glm::mat4& getProjectionMatrix();
		
	void setPosition(const glm::vec3& pos);
	glm::vec3 getPosition() const;

	void setYaw(float yaw);
	void setPitch(float pitch);

	float getYaw() const;
	float getPitch() const;

	void setFov(float fov);
	float getFov() const;

	void move(int direction, float speed = 1.5f);

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
#endif // !GRAPHICS_CAMERA_H