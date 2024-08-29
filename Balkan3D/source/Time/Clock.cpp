#include "pch.h"
#include "Time/Clock.h"

void Clock::init()
{
	m_last = (float) glfwGetTime();
}

void Clock::update(float targetFps)
{
	m_frameDuration = 1.f / targetFps;
	m_current = (float) glfwGetTime();
	m_deltaTime = m_current - m_last;

	while (m_deltaTime < m_frameDuration)
	{
		m_current = (float) glfwGetTime();
		m_deltaTime = m_current - m_last;
	}

	m_last = m_current;
}

float Clock::getDeltaTime()
{
	return m_deltaTime;
}

float Clock::getFrameDuration()
{
	return m_frameDuration;
}

float Clock::m_frameDuration;

float Clock::m_current;

float Clock::m_last;

float Clock::m_deltaTime;
