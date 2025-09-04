#include "SimpleShootComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
using namespace BalisongEngine;
using namespace BalisongEngineOCM;
using namespace BalisongEngineComponents;

#include "SpriteRendererComponent.h"
#include "MoveComponent.h"
#include "SpinComponent.h"
#include "TimerComponent.h"
#include "TestComponents.h"

#include "Input.h"
using namespace BalisongEngineFramework;

#include <glm/glm.hpp>
using namespace glm;

#include <iostream>
using namespace std;

// ===============================================================================

SimpleShootComponent::SimpleShootComponent(GameObject* go, const string& comp_name) : BaseComponent(go, comp_name) {}
SimpleShootComponent::~SimpleShootComponent() {}

// ===============================================================================

void SimpleShootComponent::Update(float dt)
{
	if (Input::GetKey(shootKeycode))
	{
		if (cooldownTimerComponent->HasTimeLeft()) return;

		cooldownTimerComponent->SetTimer(shootCooldown);

		vec2 proj_pos = transform->GetWorldPosition();

		vec2 proj_dir = moveComponent ? moveComponent->GetDirection() : vec2(0, 1);

		Shoot(proj_pos, proj_dir);
	}
}

// ===============================================================================

void SimpleShootComponent::Shoot(vec2 proj_pos, float proj_scale, float proj_speed, vec2 proj_dir, std::string proj_texture_path, float proj_lifetime)
{
	auto go = new GameObject(name + "'s Projectile");
	auto tr = go->GetTransform();
	tr->SetLocalPosition(proj_pos);
	tr->SetLocalScale(proj_scale);

	auto move = go->AddComponent<MoveComponent>();
	move->SetSpeed(proj_speed);
	move->SetDirection(proj_dir);

	auto sprite = go->AddComponent<SpriteRendererComponent>();
	sprite->SetTexture(proj_texture_path);

	auto spin = go->AddComponent<SpinComponent>();
	spin->spinSpeed = 500;

	if(proj_lifetime>0)
	go->Destroy(proj_lifetime);
}

void SimpleShootComponent::Shoot(vec2 proj_pos, vec2 proj_dir)
{
	Shoot(proj_pos, projectileScale, projectileSpeed, proj_dir, projectileTexturePath, projectileLifetime);
}