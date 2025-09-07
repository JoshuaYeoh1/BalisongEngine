#pragma once
#include "BaseComponent.h"
#include "GameObjectRef.h"
#include "GameObjectRefSet.h"
#include <glm/glm.hpp>

// ====================================================================

namespace BalisongEngine{
namespace BalisongEngineComponents
{
	class TimerComponent; // forward declare

	// ====================================================================

	/// <summary>
	/// The component to spawn and keep track of enemies, with a timer
	/// </summary>
	class EnemySpawnerComponent : public BaseComponent
	{
	public:

		/// <summary>
		/// ctor
		/// </summary>
		/// <param name="go"></param>
		/// <param name="comp_name"></param>
		EnemySpawnerComponent(BalisongEngineOCM::GameObject* go, const std::string& comp_name = "[EnemySpawnerComponent]");
		~EnemySpawnerComponent();

		void Update(float dt) override;

		// ===============================================================================
		
		/// <summary>
		/// Sets the target to assign to enemies when they spawn
		/// </summary>
		/// <param name="to"></param>
		void SetTarget(BalisongEngineOCM::GameObject* to);
		/// <summary>
		/// Gets the target reference that will be assigned to enemies when they spawn
		/// </summary>
		/// <returns></returns>
		BalisongEngineOCM::GameObjectRef GetTargetRef() const;

		// ===============================================================================

		/// <summary>
		/// The name of the prefab to spawn
		/// </summary>
		std::string prefabName = "Enemy";
		/// <summary>
		/// The maximum number of enemies to exist at one time
		/// </summary>
		int maxEnemies = 5;
		/// <summary>
		/// The random cooldown after spawning
		/// </summary>
		glm::vec2 spawnrateRange = { 2,5 };
		/// <summary>
		/// The spacing from the edge for spawning outside or inside the camera
		/// </summary>
		float expandOffset = .25f;

		// ===============================================================================

		void OnDestroy() override;

		// ===============================================================================
		
	private:

		BalisongEngineOCM::GameObjectRef targetRef;

		// ===============================================================================

		void Spawn();

		BalisongEngineOCM::GameObjectRefSet enemies;

		// ===============================================================================

		float GetRandom(glm::vec2 range);
		TimerComponent* spawnTimerComponent = nullptr;
		void RandomizeSpawnrate();
		
	};

}
}
