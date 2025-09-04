#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <glm/glm.hpp>
#include "Random.h"

// ===============================================================================

namespace BalisongEngine{

	namespace BalisongEngineComponents
	{
		class TransformComponent; // forward declare
	}

namespace BalisongEngineOCM
{
	class GameObject; // forward declare
	class Prefab; // forward declare

	// ===============================================================================
	
	/// <summary>
	/// The preset to use when trying to find and spawn somethig
	/// </summary>
	struct SpawnCfg
	{
		/// <summary>
		/// The name of the prefab to spawn
		/// </summary>
		std::string prefab_name;
		/// <summary>
		/// Other random names of prefabs to spawn 
		/// </summary>
		std::vector<std::string> prefab_names = {"a", "b", "c"};

		/// <summary>
		/// Gets one of the random prefab names to spawn
		/// </summary>
		/// <returns></returns>
		std::string GetRandomName() const
		{
			if (prefab_names.size() == 0) return prefab_name;

			std::vector<std::string> names = prefab_names;

			if(!prefab_name.empty())
			names.push_back(prefab_name);

			int i = BalisongEngineFramework::Random::Range(0, (int)names.size());
			return names[i];
		}

		/// <summary>
		/// The position to spawn
		/// </summary>
		glm::vec2 position = { 0,0 };
		/// <summary>
		/// The rotation to spawn
		/// </summary>
		float angles = 0;
		/// <summary>
		/// The scale to spawn
		/// </summary>
		glm::vec2 scale = { 1,1 };
		/// <summary>
		/// The parent to assign to after spawn
		/// </summary>
		BalisongEngineComponents::TransformComponent* parent = nullptr;
	};

	// ===============================================================================

	/// <summary>
	/// The static class to store a list of prefabs and their lookup names to find and spawn
	/// </summary>
	class PrefabManager
	{
	public:
		
		/// <summary>
		/// ctor not for static classes
		/// </summary>
		PrefabManager() = delete;
		~PrefabManager();

		// ===============================================================================

		/// <summary>
		/// Registers a prefab and its lookup name
		/// </summary>
		/// <param name="name"></param>
		/// <param name="prefab"></param>
		static void AddPrefab(const std::string& prefab_name, Prefab* prefab);
		/// <summary>
		/// Unegisters a prefab and its lookup name
		/// </summary>
		/// <param name="name"></param>
		/// <param name="prefab"></param>
		static void RemovePrefab(const std::string& prefab_name);

		// ===============================================================================

		/// <summary>
		/// Instantiate a prefab by finding its lookup name
		/// </summary>
		/// <param name="name"></param>
		/// <returns></returns>
		static GameObject* Instantiate(const std::string& prefab_name);
		/// <summary>
		/// Instantiate a prefab by finding its lookup name, then set its parent
		/// </summary>
		/// <param name="prefab_name"></param>
		/// <param name="parent"></param>
		/// <returns></returns>
		static GameObject* Instantiate(const std::string& prefab_name, BalisongEngineComponents::TransformComponent* parent);
		/// <summary>
		/// Instantiate a prefab by finding its lookup name, then set its transforms and parent
		/// </summary>
		/// <param name="prefab_name"></param>
		/// <param name="position"></param>
		/// <param name="angles"></param>
		/// <param name="scale"></param>
		/// <param name="parent"></param>
		/// <returns></returns>
		static GameObject* Instantiate(const std::string& prefab_name, glm::vec2 position, float angles = 0, glm::vec2 scale = { 1,1 }, BalisongEngineComponents::TransformComponent* parent = nullptr);
		/// <summary>
		/// Instantiate a prefab by using a spawn preset
		/// </summary>
		/// <param name="cfg"></param>
		/// <returns></returns>
		static GameObject* Instantiate(SpawnCfg cfg);

		// ===============================================================================

		/// <summary>
		/// Clears all prefabs from the list for reset
		/// </summary>
		static void ClearPrefabs();

		// ===============================================================================

	private:

		static std::unordered_map<std::string, Prefab*> prefabs;

		static Prefab* FindPrefab(const std::string& prefab_name);
		static bool HasPrefab(const std::string& prefab_name);
	};

}}