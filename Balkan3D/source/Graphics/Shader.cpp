#include "pch.h"
#include "Graphics/Shader.h"

Shader::Shader(std::string vertex, std::string fragment)
{
	const char* vertexSource = vertex.c_str();
	const char* fragmentSource = fragment.c_str();

	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	if (m_vertexShader == 0)
	{
		LOG_ERROR("Cannot create Vertex Shader");
		return;
	}

	glShaderSource(m_vertexShader, 1, &vertexSource, NULL);
	glCompileShader(m_vertexShader);
	
	m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	if (m_fragmentShader == 0)
	{
		LOG_ERROR("Cannot create Fragment Shader");
		return;
	}
	glShaderSource(m_fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(m_vertexShader);

	m_id = glCreateProgram();
	if (m_id == 0)
	{
		LOG_ERROR("Cannot create Shader Program!");
		return;
	}
	glAttachShader(m_id, m_vertexShader);
	glAttachShader(m_id, m_fragmentShader);
	glLinkProgram(m_id);
}

Shader::~Shader()
{
	glDetachShader(m_id, m_vertexShader);
	glDetachShader(m_id, m_fragmentShader);
	glDeleteShader(m_vertexShader);
	glDeleteShader(m_fragmentShader);
	glDeleteProgram(m_id);
}

void Shader::use()
{
	glUseProgram(m_id);
}

void Shader::unuse()
{
	glUseProgram(0);
}

void Shader::set1i(const char* name, GLint value)
{
	glUniform1i(glGetUniformLocation(m_id, name), value);
}

void Shader::set1f(const char* name, GLfloat value)
{
	glUniform1f(glGetUniformLocation(m_id, name), value);
}

void Shader::setvec2f(const char* name, glm::fvec2 value)
{
	glUniform2fv(glGetUniformLocation(m_id, name), 1, glm::value_ptr(value));
}

void Shader::setvec3f(const char* name, glm::fvec3 value)
{
	glUniform3fv(glGetUniformLocation(m_id, name), 1, glm::value_ptr(value));
}

void Shader::setvec4f(const char* name, glm::fvec4 value)
{
	glUniform4fv(glGetUniformLocation(m_id, name), 1, glm::value_ptr(value));
}

void Shader::setmat3fv(const char* name, glm::fmat3 value, GLboolean transpose)
{
	glUniformMatrix3fv(glGetUniformLocation(m_id, name), 1, transpose, glm::value_ptr(value));
}

void Shader::setmat4fv(const char* name, glm::fmat4 value, GLboolean transpose)
{
	glUniformMatrix4fv(glGetUniformLocation(m_id, name), 1, transpose, glm::value_ptr(value));
}

GLuint Shader::getId() const
{
	return m_id;
}
