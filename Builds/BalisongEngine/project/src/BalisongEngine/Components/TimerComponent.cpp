#include "TimerComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
using namespace BalisongEngine;
using namespace BalisongEngineOCM;
using namespace BalisongEngineComponents;

#include <glm/glm.hpp>
using namespace glm;

#include <iostream>
using namespace std;

// ===============================================================================

TimerComponent::TimerComponent(GameObject* go, const string& comp_name) : BaseComponent(go, comp_name) {}
TimerComponent::~TimerComponent() {}

// ===============================================================================

void TimerComponent::Update(float dt)
{
    if (isPaused) return;
    if (!HasTimeLeft()) return;

    secondsLeft -= dt;

    if (secondsLeft <= 0)
        secondsLeft = 0;
}

// ===============================================================================

void TimerComponent::SetTimer(float t)
{
	secondsLeft = t;
}
bool TimerComponent::HasTimeLeft()
{
	return secondsLeft > 0;
}
void TimerComponent::FinishTimer()
{
    secondsLeft = 0;
}

// ===============================================================================

float TimerComponent::GetNormalizedTimeLeft(float max)
{
    if (max <= 0 || secondsLeft <= 0)
    return 0;

    if (secondsLeft >= max)
    return 1;

    return secondsLeft / max;
}