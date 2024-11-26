#include "pch.h"
#include "Graphics/Shader.h"
#include "Logging/Loging.h"
#include <fstream>
#include <sstream>

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

	m_vertexPath = nullptr;
	m_vertexPath = nullptr;
}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::ostringstream vstream;
	std::ostringstream fstream;

	std::string vsource;
	std::string fsource;

	std::ifstream file(vertexPath);
	if (!file.is_open())
	{
		LOG_ERROR("Cannot open vertex shader in path: %s", vertexPath);
		return;
	}
	
	vstream << file.rdbuf();
	file.close();

	file.open(fragmentPath);

	if (!file.is_open())
	{
		LOG_ERROR("Cannot open fragment shader in path: %s", fragmentPath);
		return;
	}
	
	fstream << file.rdbuf();
	file.close();

	vsource = vstream.str();
	fsource = fstream.str();

	{	// vertex shader creation
		m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
		if (m_vertexShader == 0)
		{
			LOG_ERROR("Cannot create Vertex Shader");
			return;
		}

		const char *tempVsource = vsource.c_str();
		glShaderSource(m_vertexShader, 1, &tempVsource, NULL);
		glCompileShader(m_vertexShader);
	}

	{ // fragment shader creation
		m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		if (m_fragmentShader == 0)
		{
			LOG_ERROR("Cannot create Fragment Shader");
			return;
		}

		const char* tempFsource = fsource.c_str();
		glShaderSource(m_fragmentShader, 1, &tempFsource, NULL);
		glCompileShader(m_vertexShader);
	}

	{ // Shader program creation
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

	m_vertexPath = vertexPath;
	m_fragmentPath = fragmentPath;
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

char *Shader::getVertexPath() const
{
    return (char*) m_vertexPath.c_str();
}

 char *Shader::getFragmentPath() const
{
    return (char*) m_fragmentPath.c_str();
}
