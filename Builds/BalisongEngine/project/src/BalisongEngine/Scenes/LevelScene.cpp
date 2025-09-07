#include "LevelScene.h"
#include "GameObject.h"
#include "PrefabManager.h"
#include "TransformComponent.h"
#include "Renderer.h"
#include "Camera.h"
#include "SceneStateMachine.h"
using namespace BalisongEngine;
using namespace BalisongEngineOCM;
using namespace BalisongEngineComponents;
using namespace BalisongEngineRenderer;
using namespace BalisongEngineScenes;

#include "PursuitComponent.h"
#include "EnemySpawnerComponent.h"
#include "AudioSourceComponent.h"

#include "AudioManager.h"
using namespace BalisongEngineFramework;

#include <glm/glm.hpp>
using namespace glm;

#include <iostream>
using namespace std;

// ===============================================================================

EnemySpawnerComponent* enemy_spawner_comp = nullptr;

void LevelScene::OnInitialize()
{
	Renderer::SetClearColor(0, 0, 0, 1); // bg color
	Camera::SetPosition(0, 0, 0);

	// ===============================================================================
	
	time = 0;
	minTime = 0;
	maxTime = 120;
	minSpawnrate = { 2,5 };
	maxSpawnrate = { .1f,.2f };

	// ===============================================================================

	player = nullptr;
	death_time = 0;
	loseUI = nullptr;

	// ===============================================================================

	auto tutorial = PrefabManager::Instantiate("Tutorial");
	tutorial->Destroy(5);

	// ===============================================================================

	auto mouse = PrefabManager::Instantiate("Mouse");

	// ===============================================================================

	player = PrefabManager::Instantiate("Player");

	player->DestroyEvent.Subscribe(this, &LevelScene::OnPlayerDestroyed);

	auto player_pursuit = player->GetComponent<PursuitComponent>();
	player_pursuit->SetTarget(mouse);
	
	// ===============================================================================

	auto enemy_spawner = PrefabManager::Instantiate("EnemySpawner");

	enemy_spawner_comp = enemy_spawner->GetComponent<EnemySpawnerComponent>();
	enemy_spawner_comp->SetTarget(player);

	// ===============================================================================

	AudioManager::Play("ButtonPlay");
}

// ===============================================================================

void LevelScene::OnUpdate(float dt)
{
	time += dt;

	float time01 = clamp(time / maxTime, 0.0f, 1.0f);

	// lerp
	vec2 spawnrateRange = minSpawnrate + (maxSpawnrate - minSpawnrate) * time01;

	enemy_spawner_comp->spawnrateRange = spawnrateRange;

	// ===============================================================================

	if (player) return;

	death_time += dt;
	if (death_time < 1) return;
	
	if (loseUI) return;
	loseUI = PrefabManager::Instantiate("LoseUI");
}

void LevelScene::OnPlayerDestroyed(GameObject* who)
{
	if (who != player) return;

	player = nullptr;
}