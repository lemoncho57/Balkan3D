#include "pch.h"
#include "Graphics/Texture.h"
#include "Logging/Loging.h"
#include <glad/glad.h>
#include <stb_image/stb_image.h>

Texture::Texture(const char* fileName, bool flipImage)
{
	stbi_set_flip_vertically_on_load(flipImage);
	m_imageData = stbi_load(fileName, &m_width, &m_height, &m_imageChannels, 0);

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (!m_imageData)
	{
		LOG_ERROR("Failed to load the texture from file: %s", fileName);
		return;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_imageData);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(m_imageData);
}

// Texture::Texture(glm::vec4 color)
// {
// 	glGenTextures(1, &m_texture);
// 	glBindTexture(GL_TEXTURE_2D, m_texture);

// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

// 	unsigned char colorArr[4] = 
// 	{
// 		(unsigned char) color.x,
// 		(unsigned char) color.y,
// 		(unsigned char) color.z,
// 		(unsigned char) color.w
// 	};

// 	m_imageData = colorArr;

// 	if (!m_imageData)
// 	{
// 		LOG_ERROR("Failed to load the texture from color: %f %f %f %f", color.x, color.y, color.z, color.w);
// 		return;
// 	}

// 	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, colorArr);
// 	glGenerateMipmap(GL_TEXTURE_2D);
// }

Texture::~Texture()
{

}

void Texture::activateTexture(GLenum texure)
{
	glActiveTexture(texure);
}

void Texture::use()
{
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

void Texture::unuse()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int Texture::getTexture() const
{
	return m_texture;
}