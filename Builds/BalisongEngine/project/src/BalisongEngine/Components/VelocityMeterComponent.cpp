#include "VelocityMeterComponent.h"
#include "GameObject.h"
#include "GameObjectRef.h"
#include "TransformComponent.h"
using namespace BalisongEngine;
using namespace BalisongEngineOCM;
using namespace BalisongEngineComponents;

#include <glm/glm.hpp>
using namespace glm;

#include <iostream>
using namespace std;

// ===============================================================================

VelocityMeterComponent::VelocityMeterComponent(GameObject* go, const string& comp_name) : BaseComponent(go, comp_name) {}
VelocityMeterComponent::~VelocityMeterComponent() {}

// ===============================================================================

void VelocityMeterComponent::Update(float dt)
{
	auto target = targetRef.Get();

	if (!target)
	{
		velocity = { 0,0 };
		magnitude = 0;
		direction = { 0,1 };
		prevPos = { 0,0 };
		return;
	}

	auto target_tr = target->GetTransform();
	auto target_pos = target_tr->GetWorldPosition();

	velocity = (target_pos - prevPos) / dt;
	magnitude = length(velocity);
	direction = normalize(velocity);

	prevPos = target_pos;
}

// ===============================================================================

void VelocityMeterComponent::SetTarget(GameObject* to)
{
	targetRef.Set(to);
}

GameObjectRef VelocityMeterComponent::GetTargetRef() const
{
	return targetRef;
}

// ===============================================================================

vec2 VelocityMeterComponent::GetVelocity() const
{
	return velocity;
}
float VelocityMeterComponent::GetMagnitude() const
{
	return magnitude;
}
vec2 VelocityMeterComponent::GetDirection() const
{
	return direction;
}

// ===============================================================================

void VelocityMeterComponent::OnDestroy()
{
	SetTarget(nullptr);
}