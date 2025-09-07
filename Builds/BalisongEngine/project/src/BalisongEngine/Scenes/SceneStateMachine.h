#pragma once
#include <unordered_map>
#include <vector>
#include <iostream>

// ===============================================================================

namespace BalisongEngine{
namespace BalisongEngineScenes
{
	class BaseScene; // forward declare

	// ===============================================================================

	/// <summary>
	/// The static class to manage all scenes, a list of scenes to change to
	/// </summary>
	class SceneStateMachine
	{
	public:

		/// <summary>
		/// ctor not for static class
		/// </summary>
		SceneStateMachine() = delete; // disallow construction of class instance

		// ===============================================================================

		/// <summary>
		/// Add a scene to the scenes collection. Cannot be the same name as existing scenes
		/// </summary>
		/// <typeparam name="T">Any class that derives from BaseScene</typeparam>
		/// <typeparam name="">BaseScene</typeparam>
		/// <returns>Class that derives from BaseScene</returns>
		template<
			typename T,
			typename = typename std::enable_if<std::is_base_of<BaseScene, T>::value>::type
		>
		static T* AddScene()
		{
			T* new_scene = new T();

			auto pair = std::make_pair(new_scene->GetName(), new_scene);

			std::pair <std::unordered_map<std::string, BaseScene*>::iterator, bool> result = scenes.insert(pair);

			// result.first = the (std::string + Scene*) pair
			// result.second = whether the insertion is successful or not.
			//   If successful, pair.first will point o the newly inserted pair.
			//   If not successful, pair.first will point to existing pair inside the map.

			// if successfuly adding the new pair
			if (result.second)
			{
				orderedScenes.push_back(new_scene);

				unsigned int current_id = sceneIdCounter;
				sceneIdCounter++;

				std::cout << "[Scene] Added: " << new_scene->GetName() << ", ID: " << current_id << std::endl;

				return new_scene;
			}
			else
			{
				std::cout << "[Scene] Failed to add: " << new_scene->GetName() << " already exists." << std::endl;

				delete new_scene;
				return nullptr;
			}
		}

		// ===============================================================================

		/// <summary>
		/// Queues the target scene to be loaded next update
		/// </summary>
		static void LoadScene(BaseScene* scene);
		/// <summary>
		/// Queues the target scene name to be loaded next update
		/// </summary>
		/// <param name="name"></param>
		static void LoadScene(const std::string name);
		/// <summary>
		/// Queues the target scene index to be loaded next update
		/// </summary>
		/// <param name="index"></param>
		static void LoadScene(const unsigned int index);

		/// <summary>
		/// Reloads the current scene
		/// </summary>
		static void ReloadScene();
		/// <summary>
		/// Try load the next index scene
		/// </summary>
		static void LoadNextScene();
		/// <summary>
		/// Try load the previous index scene
		/// </summary>
		static void LoadPrevScene();
		
		// ===============================================================================

		/// <summary>
		/// Gets the current active scene
		/// </summary>
		/// <returns>BaseScene</returns>
		static BaseScene* GetCurrentScene();
		/// <summary>
		/// Gets the current index of active scene
		/// </summary>
		/// <returns></returns>
		static int GetCurrentSceneIndex();

		// ===============================================================================

	private:

		static int GetSceneIndex(BaseScene* scene);

		// ===============================================================================

		// Restrict these functions to only be callable by Application

		static void Update(float dt);
		static void Render();		

		// ===============================================================================

		static void Dispose();

		// Make the Application class a friend of the class containing these functions.
		// This would allow only Application to access them, 
		// while preventing other objects from doing so

		friend class Application;

		// ===============================================================================
		 		
		// sceneMap
		static std::unordered_map<std::string, BaseScene*> scenes;
		static std::vector<BaseScene*> orderedScenes;

		static BaseScene* currentScene;
		static BaseScene* nextScene;
		static unsigned int sceneIdCounter;

		static void TryChangeScene();
	};
	
}
}
