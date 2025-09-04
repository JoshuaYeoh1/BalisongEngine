#include "RandomTransformComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
using namespace BalisongEngine;
using namespace BalisongEngineOCM;
using namespace BalisongEngineComponents;

#include "Random.h"
using namespace BalisongEngineFramework;

#include <glm/glm.hpp>
using namespace glm;

#include <iostream>
using namespace std;

// ===============================================================================

RandomTransformComponent::RandomTransformComponent(GameObject* go, const string& comp_name) : BaseComponent(go, comp_name) {}
RandomTransformComponent::~RandomTransformComponent() {}

// ===============================================================================

void RandomTransformComponent::Start()
{
	Translate();
	Rotate();
	ScaleMult();
}

// ===============================================================================

void RandomTransformComponent::Translate()
{
	if (!randomTranslate) return;

	float rand_x = Random::Range(translateRange.x, translateRange.y);
	float rand_y = Random::Range(translateRange.x, translateRange.y);

	transform->TranslateLocal(
		rand_x * translateAxisMult.x,
		rand_y * translateAxisMult.y);
}

void RandomTransformComponent::Rotate()
{
	if (!randomRotate) return;

	float rand = Random::Range(rotateRange.x, rotateRange.y);

	transform->RotateLocal(rand);
}

void RandomTransformComponent::ScaleMult()
{
	if (!randomScaleMult) return;

	float rand = Random::Range(scaleMultRange.x, scaleMultRange.y);

	if (uniformScale)
	{
		transform->LocalScaleMult(rand * scaleAxisMult);
		return;
	}

	float rand_y = Random::Range(scaleMultRange.x, scaleMultRange.y);

	transform->LocalScaleMult(
		rand * scaleAxisMult.x,
		rand_y * scaleAxisMult.y);
}