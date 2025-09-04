#include "PrefabManager.h"
#include "GameObject.h"
#include "TransformComponent.h"
using namespace BalisongEngine;
using namespace BalisongEngineOCM;
using namespace BalisongEngineComponents;

#include "Prefab.h"

#include <glm/glm.hpp>
using namespace glm;

#include <iostream>
using namespace std;

// ===============================================================================

PrefabManager::~PrefabManager()
{
	ClearPrefabs();
}

// ===============================================================================

unordered_map<string, Prefab*> PrefabManager::prefabs;

// ===============================================================================

void PrefabManager::AddPrefab(const string& prefab_name, Prefab* prefab)
{
	if (HasPrefab(prefab_name)) return;

	prefabs[prefab_name] = prefab;
}

void PrefabManager::RemovePrefab(const string& prefab_name)
{
	auto it = prefabs.find(prefab_name); // Direct lookup
	// if not yet reached end, that means found one
	if (it != prefabs.end())
	{
		prefabs.erase(it);
	}
}

// ===============================================================================

GameObject* PrefabManager::Instantiate(const string& prefab_name)
{
	auto prefab = FindPrefab(prefab_name);
	if (!prefab) return nullptr;
	return prefab->CreateInstance();
}

GameObject* PrefabManager::Instantiate(const string& prefab_name, TransformComponent* parent)
{
	auto go = Instantiate(prefab_name);
	if (!go) return nullptr;

	auto tr = go->GetTransform();
	tr->SetParent(parent);

	return go;
}

GameObject* PrefabManager::Instantiate(const string& prefab_name, vec2 position, float angles, vec2 scale, TransformComponent* parent)
{
	auto go = Instantiate(prefab_name, parent);
	if (!go) return nullptr;

	auto tr = go->GetTransform();
	tr->SetLocalPosition(position);
	tr->SetLocalRotation(angles);
	tr->SetLocalScale(scale);

	return go;
}

GameObject* PrefabManager::Instantiate(SpawnCfg cfg)
{
	string prefab_name = cfg.GetRandomName();
	if (prefab_name.empty()) return nullptr;

	return Instantiate(prefab_name, cfg.position, cfg.angles, cfg.scale, cfg.parent);
}

// ===============================================================================

void PrefabManager::ClearPrefabs()
{
	prefabs.clear();
}

// ===============================================================================

Prefab* PrefabManager::FindPrefab(const string& prefab_name)
{
	auto it = prefabs.find(prefab_name); // Direct lookup
	// if not yet reached end, that means found one
	if (it != prefabs.end())
	{
		return it->second;
	}
	return nullptr;
}

bool PrefabManager::HasPrefab(const string& prefab_name)
{
	return FindPrefab(prefab_name) != nullptr;
}