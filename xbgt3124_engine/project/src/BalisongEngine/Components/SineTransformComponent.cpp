#include "SineTransformComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
using namespace BalisongEngine;
using namespace BalisongEngineOCM;
using namespace BalisongEngineComponents;

#include "TimeEngine.h"
using namespace BalisongEngineFramework;

#include <glm/glm.hpp>
using namespace glm;

#include <iostream>
using namespace std;

// ===============================================================================

SineTransformComponent::SineTransformComponent(GameObject* go, const string& comp_name) : BaseComponent(go, comp_name)
{
	RecordDefaults();
}

SineTransformComponent::~SineTransformComponent() {}

// ===============================================================================

void SineTransformComponent::RecordDefaults()
{
	defaultPos = transform->GetLocalPosition();
	defaultRot = transform->GetLocalRotation();
	defaultScale = transform->GetLocalScale();
}

// ===============================================================================

void SineTransformComponent::Update(float dt)
{
	time = TimeEngine::GetTime();

	SinePos();
	SineRot();
	SineScale();
}

// ===============================================================================

float SineTransformComponent::Sine(float freq, float ampp, float offset)
{
	if (freq != 0 && ampp != 0)
	{
		return sin(time * freq) * ampp + offset;
	}
	return offset;
}

// ===============================================================================

void SineTransformComponent::SinePos()
{
	if (!sinePos) return;

	if (posFreq == vec2(0) || posAmp == vec2(0)) return;

	vec2 sine =
	{
		Sine(posFreq.x, posAmp.x),
		Sine(posFreq.y, posAmp.y),
	};

	transform->SetLocalPosition(defaultPos + sine);
}

void SineTransformComponent::SineRot()
{
    if (!sineRot) return;

    if (rotFreq == 0 || rotAmp == 0) return;

	float sine = Sine(rotFreq, rotAmp);

	transform->SetLocalRotation(defaultRot + sine);
}

void SineTransformComponent::SineScale()
{
    if (!sineScale) return;

    if (scaleFreq == 0 || scaleAmp == 0) return;

	vec2 sine =
	{
		Sine(scaleFreq, scaleAmp, scaleAmp),
		Sine(scaleFreq, scaleAmp, scaleAmp),
	};

	transform->SetLocalScale(defaultScale + sine);
}

// ===============================================================================

void SineTransformComponent::ResetPos()
{
	transform->SetLocalPosition(defaultPos);
}

void SineTransformComponent::ResetRot()
{
	transform->SetLocalRotation(defaultRot);
}

void SineTransformComponent::ResetScale()
{
	transform->SetLocalScale(defaultScale);
}