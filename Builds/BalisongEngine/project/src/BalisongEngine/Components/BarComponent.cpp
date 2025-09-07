#include "BarComponent.h"
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

BarComponent::BarComponent(GameObject* go, const string& comp_name) : BaseComponent(go, comp_name) {}
BarComponent::~BarComponent() {}

// ===============================================================================

void BarComponent::Update(float dt)
{
	float speed = .1f;

	vec2 pos = transform->GetWorldPosition();
	vec2 new_pos = pos + speed * dt;

	transform->SetLocalPosition(new_pos);
}
