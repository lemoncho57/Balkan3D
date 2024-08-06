#include "pch.h"

namespace GraphicsUtils
{
	void GraphicsUtils::clearColor(float r, float g, float b, float a)
	{
		glClearColor((GLfloat)r, (GLfloat)g, (GLfloat)b, (GLfloat)a);
	}
}