#pragma once
#include <string>
#include <vector>
#include <set>

// ===============================================================================

namespace BalisongEngine{
namespace BalisongEngineOCM
{
	class GameObject; // forward declare

	// ===============================================================================

	/// <summary>
	/// A single global-scoped object that runs the methods of the GameObjects in its list, and checks them every frame
	/// </summary>
	class GameObjectCollection
	{
	public:

		/// <summary>
		/// ctor not for static class
		/// </summary>
		GameObjectCollection() = delete;

		// ===============================================================================

		/// <summary>
		/// Adds GameObject to gameObjects and gameObjectsToAdd collections
		/// </summary>
		/// <param name="go">GameObject/param>
		static void Add(GameObject* go);

		// ===============================================================================

		/// <summary>
		/// Updates the lifecycle of game objects by removing flagged objects, running Awake and Start for new objects, clearing the addition queue, and updating all active objects with delta time
		/// </summary>
		/// <param name="dt">deltaTime</param>
		static void Update(float dt);
		/// <summary>
		/// Runs the Render method for all components in all game objects in the collection
		/// </summary>
		static void Render();
		/// <summary>
		/// Called when the current scene is being deactivated or destroyed
		/// </summary>
		static void Dispose();

		// ===============================================================================

		// CHALLENGE
		// Refer to Unity's GameObject.Find(...) and replicate it
		//
		// Do this in GameObjectCollection.cpp
		
		/// <summary>
		/// Goes through the collection to find the first game object name that matches the target name
		/// </summary>
		/// <param name="name">Target name</param>
		/// <returns>GameObject</returns>
		static GameObject* Find(std::string name);

		// ===============================================================================

		/// <summary>
		/// Gets all game objects in the collection
		/// </summary>
		/// <returns>unordered_set GameObject</returns>
		static std::set<GameObject*>& GetAll();

		// ===============================================================================

	private:

		//static std::vector<GameObject*> gameObjects;
		//static std::vector<GameObject*> gameObjectsToAdd;

		// std::unordered_set automatically ensures that each element is unique,
		// thanks to the way it handles hashing and equality checks.
		// If you attempt to insert an element that already exists, it won't be added again.
		static std::set<GameObject*> gameObjects;
		static std::set<GameObject*> gameObjectsJustAdded;
	};
}}
