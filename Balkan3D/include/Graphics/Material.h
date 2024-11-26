#ifndef GRAPHICS_MATERIAL_H
#define GRAPHICS_MATERIAL_H
#include "../Defines.h"
#include <glm/glm.hpp>

extern "C" struct BALKAN3D_API Material
{
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
};



#endif // GRAPHICS_MATERIAL_H