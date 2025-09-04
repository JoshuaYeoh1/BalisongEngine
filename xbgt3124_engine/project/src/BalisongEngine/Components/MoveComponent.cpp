#include "MoveComponent.h"
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

MoveComponent::MoveComponent(GameObject* go, const string& comp_name) : BaseComponent(go, comp_name) {}

MoveComponent::~MoveComponent()
{
	MoveToggledEvent.UnsubscribeAll();
}

// ===============================================================================

void MoveComponent::Update(float dt)
{
	velocity = speed * direction;

	transform->TranslateLocal(velocity * dt);

	if (faceMoveDirection) transform->FaceDirection(direction, angleOffset);
	
	//cout << "dir: " << direction.x << "," << direction.y << endl;

	TryToggleMoveEvent();
}

// ===============================================================================

void MoveComponent::SetSpeed(float to)
{
	speed = to;
}
float MoveComponent::GetSpeed() const
{
	return speed;
}

// ===============================================================================

void MoveComponent::SetDirection(vec2 to)
{
	if (length(to) == 0) return;

	// digitalized normalize (length must always be 1)
	direction = normalize(to);
}
vec2 MoveComponent::GetDirection() const
{
	return direction;
}

// ===============================================================================

vec2 MoveComponent::GetVelocity() const
{
	return velocity;
}

// ===============================================================================

void MoveComponent::TryToggleMoveEvent()
{
	if (speed > 0.1f)
	{
		if (!hasMoved)
		{
			hasMoved = true;
			MoveToggledEvent.Invoke(true);
		}
	}
	else
	{
		if (hasMoved)
		{
			hasMoved = false;
			MoveToggledEvent.Invoke(false);
		}
	}
}