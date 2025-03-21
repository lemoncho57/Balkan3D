#include "pch.h"
#include "Graphics/Framebuffer.h"
#include "Logging/Loging.h"

Framebuffer::Framebuffer(int width, int heigth)
    : colorTex(width, heigth), rbo(width, heigth)
{
    glGenFramebuffers(1, (GLuint*) &FBO);
    if (!FBO)
    {
        LOG_ERROR("Unable to create framebuffer!\n");
        return;
    }

    this->bind();

    colorTex.bind();
    this->attachTexture(&colorTex);
    colorTex.unbind();

    rbo.bind();
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, (GLuint) rbo.getRBO());
    rbo.unbind();

    m_width = width;
    m_heigth = heigth;

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        LOG_ERROR("Framebuffer is NOT complete!");
        return;
    }

    this->unbind();
}

Framebuffer::~Framebuffer()
{
    glDeleteFramebuffers(1, &FBO);
}

void Framebuffer::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}

void Framebuffer::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::attachTexture(TextureAttachment* tex)
{
    if (isFramebufferBound(&FBO))
    {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex->getTextureID(), 0);
    }else
    {
        this->bind();
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex->getTextureID(), 0);
        this->unbind();
    }
}

unsigned int Framebuffer::getFBO() const
{
    return FBO;
}

RenderBufferObject Framebuffer::getRBO() const
{
    return rbo;
}

bool Framebuffer::isFramebufferBound(const unsigned int* FBOtoCheck)
{
    GLuint currentlyBoundFBO;
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, (GLint*)&currentlyBoundFBO);
    if (*FBOtoCheck != currentlyBoundFBO)
        return false;
    return true;
}

RenderBufferObject::RenderBufferObject(int width, int heigth)
{
    glGenRenderbuffers(1, &RBO);
    if (!RBO)
    {
        LOG_ERROR("Unable to create RenderBufferObject!");
        return;
    }

    this->bind();

    m_width = width;
    m_heigth = heigth;

    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, heigth);
    this->unbind();
}

RenderBufferObject::~RenderBufferObject()
{
    glDeleteRenderbuffers(1, &RBO);
}

void RenderBufferObject::bind()
{
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
}

void RenderBufferObject::unbind()
{
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

TextureAttachment::TextureAttachment(int width, int height)
{
    glGenTextures(1, &m_texture);
    glBindBuffer(GL_TEXTURE_2D,(GLuint) m_texture);

    // Not sure about the width and height
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_INT, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    m_width = width;
    m_heigth = height;

    glBindTexture(GL_TEXTURE_2D, 0);
}

TextureAttachment::~TextureAttachment()
{
    glDeleteTextures(1, &m_texture);
}

void TextureAttachment::bind()
{
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

void TextureAttachment::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
