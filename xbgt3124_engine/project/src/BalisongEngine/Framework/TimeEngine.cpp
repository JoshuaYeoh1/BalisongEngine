#include "TimeEngine.h"
using namespace BalisongEngine;
using namespace BalisongEngineFramework;

#include <glfw/glfw3.h>

// ====================================================================

// static variables
static float currentTime = 0.0f;
static float prevTime = 0.0f;
static float deltaTime = 0.0f;

// ====================================================================

float TimeEngine::GetTime()
{
	return currentTime;

}
float TimeEngine::GetDeltaTime()
{
	return deltaTime;
}

// ====================================================================

void TimeEngine::ProcessTime(float frame_time)
{
	currentTime = (float)glfwGetTime();
	deltaTime = currentTime - prevTime;

	do
	{
		currentTime = (float)glfwGetTime();
		deltaTime = currentTime - prevTime;
	}
	while (deltaTime < frame_time);

	prevTime = currentTime;
}