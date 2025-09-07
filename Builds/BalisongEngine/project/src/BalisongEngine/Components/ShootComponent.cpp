#include "ShootComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
using namespace BalisongEngine;
using namespace BalisongEngineOCM;
using namespace BalisongEngineComponents;

#include "TimerComponent.h"
#include "MoveComponent.h"
#include "TestComponents.h"

#include "PrefabManager.h"

#include "Input.h"
#include "Random.h"
using namespace BalisongEngineFramework;

#include <glm/glm.hpp>
using namespace glm;

#include <iostream>
using namespace std;

// ===============================================================================

ShootComponent::ShootComponent(GameObject* go, const string& comp_name) : BaseComponent(go, comp_name)
{
	RandomizeCooldown();
}

ShootComponent::~ShootComponent() {}

// ===============================================================================

void ShootComponent::Update(float dt)
{
	if (cooldownTimerComponent->HasTimeLeft()) return;
	
	if (autoFire && targetRef.Get()) { Shoot(); return; }

	if (useKey && shootKeyCode != KeyCode::UNKNOWN)
	{
		if (holdFiring) if (Input::GetKey(shootKeyCode)) Shoot();
		else if (Input::GetKeyDown(shootKeyCode)) Shoot();
	}

	if (useMouse && shootMouseCode != MouseCode::UNKNOWN)
	{
		if (holdFiring) if (Input::GetMouse(shootMouseCode)) Shoot();
		else if (Input::GetMouseDown(shootMouseCode)) Shoot();
	}
}

// ===============================================================================

void ShootComponent::Shoot()
{
	RandomizeCooldown();

	if (!firepoint) return;

	vec2 pos = firepoint->GetWorldPosition();
	vec2 dir = firepoint->TransformDirection(firepointDir);

	// ===============================================================================

	auto go = PrefabManager::Instantiate(prefabName, pos);
	auto tr = go->GetTransform();

	auto move = go->GetComponent<MoveComponent>();

	if (move)
	{
		move->SetSpeed(speed);

		float inaccuracy = GetRandom(inaccuracyRange);
		tr->FaceDirection(dir, angleOffset + inaccuracy);
		move->SetDirection(tr->GetLocalUp());
	}

	/*MoveComponent* move = nullptr;
	if (go->TryGetComponent(move))*/

	// ===============================================================================

	float recoil = GetRandom(recoilRange);
	transform->TranslateLocal(-dir * recoil);

	// ===============================================================================

	if(lifetime>0)
	go->Destroy(lifetime);

	// ===============================================================================

	Muzzle();

	ShootEvent.Invoke();
}

// ===============================================================================

void ShootComponent::Muzzle()
{
	vec2 pos = firepoint->GetWorldPosition();
	vec2 dir = firepoint->TransformDirection(firepointDir);

	// ===============================================================================

	auto go = PrefabManager::Instantiate(muzzlePrefabName, pos);
	auto tr = go->GetTransform();
	tr->FaceDirection(dir, angleOffset);
}

// ===============================================================================

float ShootComponent::GetRandom(vec2 range)
{
	return Random::Range(range.x, range.y);
}

void ShootComponent::RandomizeCooldown()
{
	gameObject->EnforceComponent(cooldownTimerComponent);

	auto t = GetRandom(cooldownRange);
	cooldownTimerComponent->SetTimer(t);
}

