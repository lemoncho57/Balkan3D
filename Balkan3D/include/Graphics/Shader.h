#ifndef GRAPHICS_SHADER_H
#define GRAPHICS_SHADER_H
#include "../Defines.h"

#include <string>
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>


typedef unsigned int GLuint;
typedef int GLint;
typedef float GLfloat;
typedef unsigned char GLboolean;

extern "C" class BALKAN3D_API Shader
{
public:
	Shader(std::string vertex, std::string fragment);
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void use();
	void unuse();

	void set1i(const char* name, GLint value);
	void set1f(const char* name, GLfloat value);
	void setvec2f(const char* name, glm::fvec2 value);
	void setvec3f(const char* name, glm::fvec3 value);
	void setvec4f(const char* name, glm::fvec4 value);
	void setmat3fv(const char* name, glm::fmat3 value, GLboolean transpose = 0);
	void setmat4fv(const char* name, glm::fmat4 value, GLboolean transpose = 0);

	GLuint getId() const;

private:
	GLuint m_id;
	GLuint m_vertexShader;
	GLuint m_fragmentShader;
};
#endif //GRAPHICS_SHADER_H