#include "PlayerMoveComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
using namespace BalisongEngine;
using namespace BalisongEngineOCM;
using namespace BalisongEngineComponents;

#include "MoveComponent.h"

#include "Input.h"
using namespace BalisongEngineFramework;

#include <glm/glm.hpp>
using namespace glm;

#include <iostream>
using namespace std;

// ===============================================================================

PlayerMoveComponent::PlayerMoveComponent(GameObject* go, const string& comp_name) : BaseComponent(go, comp_name) {}
PlayerMoveComponent::~PlayerMoveComponent() {}

// ===============================================================================

void PlayerMoveComponent::Update(float dt)
{
	vec2 move_input = { Input::GetAxis("Horizontal"), Input::GetAxis("Vertical") };

	float move_magnitude = length(move_input);

	// analog normalize (length must be 0-1)
	float mult = move_magnitude > 1 ? 1 : move_magnitude;

	moveComponent->SetSpeed(moveSpeed * mult);

	moveComponent->SetDirection(move_input);	
}

// ===============================================================================

void PlayerMoveComponent::Init(MoveComponent* move_comp, float start_speed, vec2 start_dir)
{
	moveComponent = move_comp;

	moveSpeed = start_speed;
	baseMoveSpeed = start_speed;

	if (start_dir == vec2(0))
	{
		start_dir = { 0,1 };
	}
	moveComponent->SetDirection(start_dir);
}

// ===============================================================================

float PlayerMoveComponent::GetMoveSpeed()
{
	return moveSpeed;
}
void PlayerMoveComponent::SetMoveSpeed(float to)
{
	moveSpeed = to;
}
void PlayerMoveComponent::RevertMoveSpeed()
{
	moveSpeed = baseMoveSpeed;
}
