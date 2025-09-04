#include "EnemySpawnerComponent.h"
#include "GameObject.h"
#include "GameObjectRef.h"
#include "GameObjectRefSet.h"
#include "TransformComponent.h"
using namespace BalisongEngine;
using namespace BalisongEngineOCM;
using namespace BalisongEngineComponents;

#include "TimerComponent.h"
#include "PursuitComponent.h"
#include "ShootComponent.h"

#include "PrefabManager.h"

#include "Random.h"
using namespace BalisongEngineFramework;

#include "Camera.h"
using namespace BalisongEngineRenderer;

#include <glm/glm.hpp>
using namespace glm;

#include <iostream>
using namespace std;

// ===============================================================================

EnemySpawnerComponent::EnemySpawnerComponent(GameObject* go, const string& comp_name) : BaseComponent(go, comp_name)
{
	gameObject->EnforceComponent(spawnTimerComponent);

	RandomizeSpawnrate();
}

EnemySpawnerComponent::~EnemySpawnerComponent() {}

// ===============================================================================

void EnemySpawnerComponent::Update(float dt)
{
	if (spawnTimerComponent->HasTimeLeft()) return;
	RandomizeSpawnrate();

	Spawn();
}

// ===============================================================================

void EnemySpawnerComponent::SetTarget(GameObject* to)
{
	targetRef.Set(to);
}

GameObjectRef EnemySpawnerComponent::GetTargetRef() const
{
	return targetRef;
}

// ===============================================================================

void EnemySpawnerComponent::Spawn()
{
	auto target = targetRef.Get();
	if (!target) return;
	
	if (enemies.Count() >= maxEnemies && maxEnemies >= 0) return;

	vec2 pos = Camera::GetRandomBounds(expandOffset);

	auto enemy = PrefabManager::Instantiate(prefabName, pos);

	if(!enemy) { cerr << bothNames << ": Failed to instantiate prefab: " << prefabName << endl; return; }

	if (auto pursuit = enemy->GetComponent<PursuitComponent>())
	{
		pursuit->SetTarget(target);
	}

	if (auto shoot = enemy->GetComponent<ShootComponent>())
	{
		shoot->targetRef.Set(target);
	}

	enemies.Add(enemy);
}

// ===============================================================================

float EnemySpawnerComponent::GetRandom(glm::vec2 range)
{
	return Random::Range(range.x, range.y);
}

void EnemySpawnerComponent::RandomizeSpawnrate()
{
	auto t = GetRandom(spawnrateRange);
	spawnTimerComponent->SetTimer(t);
}

// ===============================================================================

void EnemySpawnerComponent::OnDestroy()
{
	SetTarget(nullptr);
	enemies.RemoveAll();
}