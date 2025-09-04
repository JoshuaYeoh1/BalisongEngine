#include "BaseScene.h"
using namespace BalisongEngine;
using namespace BalisongEngineScenes;

#include "ColliderManager.h"
#include "GameObjectCollection.h"
using namespace BalisongEngineOCM;

// ===============================================================================

// NOTE: For gameObject related calls, use GameObjectCollection!

// Called first when changed to this scene.
void BaseScene::Initialize()
{
	isActive = true;

	// 1. Call initialize callback
	OnInitialize();
}

// Called second when changed to this scene.
void BaseScene::Activate()
{
	isActive = true;

	// 1. Call the relevant virtual function callback
	OnActivate();
}

// Called before changing to different scene.
void BaseScene::Deactivate()
{
	isActive = false;

	// 1. Dispose all gameObjects
	ColliderManager::Dispose();
	GameObjectCollection::Dispose();

	// 2. Call the relevant virtual function callback
	OnDeactivate();
}

// ===============================================================================

void BaseScene::Update(float dt)
{
	if (!isActive) return;

	// 1. Update all gameObjects
	GameObjectCollection::Update(dt);
	ColliderManager::Update(dt);

	// 2. Call the relevant virtual function callback
	OnUpdate(dt);
}

void BaseScene::Render()
{
	if (!isActive) return;

	// 1. Render all gameObjects
	GameObjectCollection::Render();

	// 2. Call the relevant virtual function callback
	OnRender();
}
