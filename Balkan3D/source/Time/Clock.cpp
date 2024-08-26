#include "pch.h"
#include "Time/Clock.h"

void Clock::update(float targetFps)
{
	m_targetFps = 1.f / targetFps;
	m_current = (float) glfwGetTime();
	m_deltaTime = m_current - m_last;

	if (m_current - m_last >= m_targetFps)
		m_last = m_current;
}

float Clock::getDeltaTime()
{
	return m_deltaTime;
}

float Clock::getTargetFps()
{
	return m_targetFps;
}

float Clock::m_targetFps;

float Clock::m_current;

float Clock::m_last;

float Clock::m_deltaTime;
