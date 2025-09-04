#include "GameObjectCollection.h"
#include "GameObject.h"
#include "TransformComponent.h"
using namespace BalisongEngine; // To reduce code noise
using namespace BalisongEngineComponents;
using namespace BalisongEngineOCM;

using namespace std;

// ===============================================================================

set<GameObject*> GameObjectCollection::gameObjects;
set<GameObject*> GameObjectCollection::gameObjectsJustAdded;

// ===============================================================================

void GameObjectCollection::Add(GameObject* go)
{
	gameObjectsJustAdded.insert(go);
	gameObjects.insert(go);
}

// ===============================================================================

void DeleteFlagged(set<GameObject*>& game_objects)
{
	for (auto it = game_objects.begin(); it != game_objects.end();)
	{
		GameObject* go = *it;

		if (go->ShouldDestroy())
		{
			delete go;
			it = game_objects.erase(it);
		}
		else it++;
	}
}

// ===============================================================================

void RunAwakes(set<GameObject*>& game_objects)
{
	for (auto* go : game_objects)
	{
		go->RunComponentAwake();
	}
}

void RunStarts(set<GameObject*>& game_objects)
{
	for (auto* go : game_objects)
	{
		go->RunComponentStart();
	}
}

void RunUpdates(set<GameObject*>& game_objects, float dt)
{
	for (auto* go : game_objects)
	{
		go->RunComponentUpdate(dt);
	}
}

void RunRenders(set<GameObject*>& game_objects)
{
	for (auto* go : game_objects)
	{
		go->RunComponentRender();
	}
}

// ===============================================================================

void GameObjectCollection::Update(float dt)
{
	// 1. Remove any gameObject in gameObjects array that are flagged for removal
	DeleteFlagged(gameObjects);
	// 2. For all element in gameObjectsToAdd, run its awake fn
	RunAwakes(gameObjectsJustAdded);
	// 3. For all element in gameObjectsToAdd, run its start fn
	RunStarts(gameObjectsJustAdded);
	// 4. clear gameObjectsToAdd
	gameObjectsJustAdded.clear();
	// 5. For all element in gameObjects, run its update(deltaTime) fn
	RunUpdates(gameObjects, dt);
}

void GameObjectCollection::Render()
{
	// For all element in gameObjects, run its render() fn
	RunRenders(gameObjects);
}

// ===============================================================================

void DeleteAll(set<GameObject*>& game_objects)
{
	for (auto it = game_objects.begin(); it != game_objects.end();)
	{
		GameObject* go = *it;
		delete go;
		it = game_objects.erase(it);
	}
}

// This function is to be called when the current scene is being deactivated or destroyed.
// With SceneStateMachine:
// - current scene is deactivated before changing to a different scene.
void GameObjectCollection::Dispose()
{
	// delete all element in gameObjects
	DeleteAll(gameObjects);
	// clear gameObjects array
	gameObjects.clear();
	// clear gameObjectsToAdd array
	gameObjectsJustAdded.clear();
}

// ===============================================================================

GameObject* GameObjectCollection::Find(string name)
{
	// Find the first game object that matches the name and return it.
	for (auto* go : gameObjects)
	{
		if (go->name == name) return go;
	}
	return nullptr;
}

// ===============================================================================

set<GameObject*>& GameObjectCollection::GetAll()
{
	return gameObjects;
}