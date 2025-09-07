#include "SpawnOnCollideComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
using namespace BalisongEngine;
using namespace BalisongEngineOCM;
using namespace BalisongEngineComponents;

#include "PrefabManager.h"

#include "Random.h"
using namespace BalisongEngineFramework;

#include <glm/glm.hpp>
using namespace glm;

#include <iostream>
using namespace std;

// ===============================================================================

SpawnOnCollideComponent::SpawnOnCollideComponent(GameObject* go, const string& comp_name) : BaseComponent(go, comp_name) {}
SpawnOnCollideComponent::~SpawnOnCollideComponent() {}

// ===============================================================================

void SpawnOnCollideComponent::OnCollisionEnter(GameObject* other)
{
	Spawn();
}

// ===============================================================================

void SpawnOnCollideComponent::Spawn()
{
	int count = GetRandom(spawnCountRange);

	auto pos = useCustomSpawnPos ? spawnPos : transform->GetWorldPosition();
	auto rot = useCustomSpawnRot ? spawnRot : transform->GetWorldRotation();
	auto scale = useCustomSpawnScale ? spawnScale : transform->GetWorldScale();

	for (int i = 0; i < count; i++)
	{
		PrefabManager::Instantiate(prefabName, pos, rot, scale);
	}
}

int SpawnOnCollideComponent::GetRandom(ivec2 range)
{
	return Random::Range(range.x, range.y);
}