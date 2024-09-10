#ifndef GRAPHICS_LIGHT_H
#define GRAPHICS_LIGHT_H

#include "../Defines.h"
#include <glm/glm.hpp>

extern "C" class BALKAN3D_API Light
{
public:

public:
    glm::vec3 color;
    glm::vec3 pos;
private:
};
#endif // !GRAPHICS_LIGHT_H