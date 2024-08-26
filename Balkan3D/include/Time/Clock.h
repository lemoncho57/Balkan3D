#pragma once
#include "Core.h"

extern "C" class BALKAN3D_API Clock
{
public:
	static void update(float targetFps);
	static float getDeltaTime();
	static float getTargetFps();

private:
	 static float m_targetFps;
	 static float m_current;
	 static float m_last;
	 static float m_deltaTime;
};