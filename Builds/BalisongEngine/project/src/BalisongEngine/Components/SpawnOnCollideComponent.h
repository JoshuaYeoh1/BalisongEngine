#pragma once
#include "BaseComponent.h"
#include <glm/glm.hpp>

// ================================================================================

namespace BalisongEngine{
namespace BalisongEngineComponents
{
	/// <summary>
	/// The component to spawn a prefab on collision enter
	/// </summary>
	class SpawnOnCollideComponent : public BaseComponent
	{
	public:

		/// <summary>
		/// ctor
		/// </summary>
		/// <param name="go"></param>
		/// <param name="comp_name"></param>
		SpawnOnCollideComponent(BalisongEngineOCM::GameObject* go, const std::string& comp_name = "[SpawnOnCollideComponent]");
		~SpawnOnCollideComponent();

		void OnCollisionEnter(BalisongEngineOCM::GameObject* other) override;

		// ================================================================================

		/// <summary>
		/// The name of the prefab to look for and spawn
		/// </summary>
		std::string prefabName = "BulletImpact";

		/// <summary>
		/// The random number of prefabs to spawn
		/// </summary>
		glm::ivec2 spawnCountRange = { 1,2 };

		/// <summary>
		/// If should spawn at a different place
		/// </summary>
		bool useCustomSpawnPos = false;
		/// <summary>
		/// The custom spawn position
		/// </summary>
		glm::vec2 spawnPos = { 0,0 };

		/// <summary>
		/// If should spawn with a different rotation
		/// </summary>
		bool useCustomSpawnRot = false;
		/// <summary>
		/// The custom spawn rotation
		/// </summary>
		float spawnRot = 0;

		/// <summary>
		/// If should spawn with a different scale
		/// </summary>
		bool useCustomSpawnScale = false;
		/// <summary>
		/// The custom spawn scale
		/// </summary>
		glm::vec2 spawnScale = { 1,1 };

	private:

		void Spawn();

		int GetRandom(glm::ivec2 range);

	};

}
}

