#ifndef GRAPHICS_FRAMEBUFFER_H
#define GRAPHICS_FRAMEBUFFER_H
#include "../Defines.h"
#include "Graphics/Texture.h"

extern "C" class BALKAN3D_API Framebuffer
{
public:
    Framebuffer();
    ~Framebuffer();

    void bind();
    void unbind();

    void attachTexture(Texture& tex);

    unsigned int getFBO() const;

private:
    unsigned int FBO;
};

#endif //GRAPHICS_FRAMEBUFFER_H
