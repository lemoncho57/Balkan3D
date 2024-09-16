#ifndef GRAPHICS_TEXTURE_H
#define GRAPHICS_TEXTURE_H
#include "../Defines.h"

typedef unsigned int GLenum;
typedef unsigned int GLuint;
extern "C" class BALKAN3D_API Texture
{
public:
	Texture(const char* fileName, bool flipImage = true);
	~Texture();

	void activateTexture(GLenum texure);

	void use();
	void unuse();

private:
	int m_width;
	int m_height;
	int m_imageChannels;

	unsigned char* m_imageData;
	GLuint m_texture;
};
#endif //!GRAPHICS_TEXTURE_H