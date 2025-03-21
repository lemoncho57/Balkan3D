#ifndef GRAPHICS_FRAMEBUFFER_H
#define GRAPHICS_FRAMEBUFFER_H
#include "../Defines.h"
#include "Graphics/Texture.h"

extern "C" struct BALKAN3D_API TextureAttachment
{
    TextureAttachment(int width, int height);
    ~TextureAttachment();

    void bind();
    void unbind();

    unsigned int getTextureID() const
    {
        return m_texture;
    }
private:
    unsigned int m_texture;
    int m_width;
    int m_heigth;
};

struct RenderBufferObject
{
    RenderBufferObject(int width, int heigth);
    ~RenderBufferObject();

    unsigned int getRBO() const
    {
        return RBO;
    }

    void bind();
    void unbind();
private:
    unsigned int RBO;
    int m_width;
    int m_heigth;
};

extern "C" class BALKAN3D_API Framebuffer
{
public:
    Framebuffer(int width, int heigth);
    ~Framebuffer();

    void bind();
    void unbind();

    void attachTexture(TextureAttachment* tex);

    unsigned int getFBO() const;
    RenderBufferObject getRBO() const;
private:
    // Checks if FBOtoCheck is bound to the currently bound framebuffer
    bool isFramebufferBound(const unsigned int* FBOtoCheck);

private:
    unsigned int FBO;
    TextureAttachment colorTex;
    RenderBufferObject rbo;
    int m_width;
    int m_heigth;
};

#endif //GRAPHICS_FRAMEBUFFER_H
