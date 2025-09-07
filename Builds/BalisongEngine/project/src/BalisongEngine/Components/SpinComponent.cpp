#include "SpinComponent.h"
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

SpinComponent::SpinComponent(GameObject* go, const string& comp_name) : BaseComponent(go, comp_name) {}
SpinComponent::~SpinComponent() {}

// ===============================================================================

void SpinComponent::Update(float dt)
{
	transform->RotateLocal(spinSpeed * dt);
}
