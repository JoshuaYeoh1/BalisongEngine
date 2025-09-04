#include "SceneStateMachine.h"
using namespace BalisongEngine;

#include "BaseScene.h"
using namespace BalisongEngineScenes;

#include <iostream>
using namespace std;

// ===============================================================================

unordered_map<string, BaseScene*> SceneStateMachine::scenes;
vector<BaseScene*> SceneStateMachine::orderedScenes;

BaseScene* SceneStateMachine::currentScene = nullptr;
BaseScene* SceneStateMachine::nextScene = nullptr;
unsigned int SceneStateMachine::sceneIdCounter;

// ===============================================================================

void SceneStateMachine::Update(float dt)
{
	// Update current scene if there is one.
	if (currentScene && currentScene->isActive)
	{
		currentScene->Update(dt);
	}

	TryChangeScene();
}

void SceneStateMachine::Render()
{
	// Render current scene if there is one.
	if (currentScene && currentScene->isActive)
	{
		currentScene->Render();
	}
}

// ===============================================================================

void SceneStateMachine::Dispose()
{
	// Dispose all currently active gameObjects.
	if (currentScene) currentScene->Deactivate();

	// For each element in scenes
	for (auto it = scenes.begin(); it != scenes.end();)
	{
		// Delete the element
		delete it->second;
		// Erase the element from the map
		it = scenes.erase(it);
	}

	// Clear the collection
	scenes.clear();
	// Reset sceneIdCounter
	sceneIdCounter = 0;
	// Set currentScene to nullptr for safety.
	currentScene = nullptr;
}

// ===============================================================================

void SceneStateMachine::LoadScene(BaseScene* scene)
{
	nextScene = scene;
}

void SceneStateMachine::LoadScene(const string name)
{
	cout << "\n[Scene] Trying to load name: " << name << endl;

	// The iterator
	unordered_map<string, BaseScene*>::iterator it;

	// Look for the scene matching the name
	for (it = scenes.begin(); it != scenes.end(); it++)
	{
		auto scene_name = it->first;
		auto scene = it->second;
	
		// If found:
		if (scene_name == name)
		{
			LoadScene(scene);
			return;
		}
	}
	// Otherwise, log error
	cout << "[Scene] Couldn't find name: " << name << endl;
}

void SceneStateMachine::LoadScene(const unsigned int index)
{
	cout << "[Scene] Trying to load index: " << index << endl;

	// Add functionality to load scene by index
	// The index is 0-based, and is ordered by AddScene calls.
	// Refer to Unity for how they do loadScene by index.
	// Hint #1: You will need another collection.
	// Hint #2: You will need to alter AddScene in .h file

	// ignore if no scenes
	if (orderedScenes.size() <= 0)
	{
		cout << "[Scene] No scenes yet boi\n";
		return;
	}

	// ignore if index out of range
	if (index < 0 && index >= orderedScenes.size())
	{
		cout << "[Scene] Couldn't find index: " << index << endl;
		return;
	}

	nextScene = orderedScenes[index];
}

void SceneStateMachine::ReloadScene()
{
	LoadScene(GetCurrentScene());
}
void SceneStateMachine::LoadNextScene()
{
	LoadScene(GetCurrentSceneIndex() + 1);
}
void SceneStateMachine::LoadPrevScene()
{
	LoadScene(GetCurrentSceneIndex() - 1);
}

// ===============================================================================

BaseScene* SceneStateMachine::GetCurrentScene()
{
	// Return the currently active scene
	return currentScene;
	// Game developers would need to cast to concrete type themselves,
	// but that is not the issue you need to solve.
}

int SceneStateMachine::GetCurrentSceneIndex()
{
	return GetSceneIndex(currentScene);
}

// ===============================================================================

int SceneStateMachine::GetSceneIndex(BaseScene* scene)
{
	for (size_t i = 0; i < orderedScenes.size(); i++)
	{
		if (orderedScenes[i] == scene)
		{
			return static_cast<int>(i); // Return index as int
		}
	}
	return -1; // Return -1 if not found in orderedScenes
}

// ===============================================================================

void SceneStateMachine::TryChangeScene()
{
	if (!nextScene) return;

	// Deactivate currentScene, if there is one
	// (Note: there won't be one on launch!)
	// (Disposes all currently active gameObjects)
	if (currentScene)
	{
		cout << "[Scene] Deactivating: " << currentScene->GetName() << ", ID: " << GetCurrentSceneIndex() << "\n\n";

		currentScene->Deactivate();
		currentScene = nullptr;
	}

	// Point currentScene to nextScene.
	currentScene = nextScene;
	// Revert nextScene back to null.
	nextScene = nullptr;

	cout << "\n[Scene] Changed to: " << currentScene->GetName() << ", ID: " << GetCurrentSceneIndex() << "\n\n";

	// Initialize and activate the new scene.
	currentScene->Initialize();
	currentScene->Activate();
}
