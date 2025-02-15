#include "pch.h"
#include "Graphics/Framebuffer.h"
#include "Logging/Loging.h"

Framebuffer::Framebuffer()
{
    glGenFramebuffers(1, (GLuint*) &FBO);
    if (!FBO)
    {
        LOG_ERROR("Unable to create framebuffer!\n");
        return;
    }
    // glBindFramebuffer(GL_FRAMEBUFFER, FBO); // testing

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        LOG_ERROR("Framebuffer is NOT complete!");
        return;
    }
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

void Framebuffer::attachTexture(Texture& tex)
{
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex.getTexture(), 0);
}

unsigned int Framebuffer::getFBO() const
{
    return FBO;
}
