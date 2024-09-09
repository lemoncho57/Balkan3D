#include "pch.h"
#include "Graphics/GraphicsUtils.h"

namespace GraphicsUtils
{
	void clearColor(float r, float g, float b, float a)
	{
		glClearColor((GLfloat)r, (GLfloat)g, (GLfloat)b, (GLfloat)a);
	}
}