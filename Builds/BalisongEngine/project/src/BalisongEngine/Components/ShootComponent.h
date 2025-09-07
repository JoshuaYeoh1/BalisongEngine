#pragma once
#include "BaseComponent.h"
#include "Input.h"
#include <glm/glm.hpp>
#include "ActionEvent.h"
#include "GameObjectRef.h"

// ====================================================================

namespace BalisongEngine{
namespace BalisongEngineComponents
{
	class TransformComponent; // forward declare
	class TimerComponent; // forward declare

	// ====================================================================

	/// <summary>
	/// The component to spawn projectile prefabs, can be manual or automatic
	/// </summary>
	class ShootComponent : public BaseComponent
	{
	public:

		/// <summary>
		/// ctor
		/// </summary>
		/// <param name="go"></param>
		/// <param name="comp_name"></param>
		ShootComponent(BalisongEngineOCM::GameObject* go, const std::string& comp_name = "[ShootComponent]");
		~ShootComponent();

		void Update(float dt) override;

		// ===============================================================================
		
		/// <summary>
		/// If should detect keyboard inputs
		/// </summary>
		bool useKey = false;
		/// <summary>
		/// The type of key to detect
		/// </summary>
		BalisongEngineFramework::KeyCode shootKeyCode = BalisongEngineFramework::KeyCode::UNKNOWN;

		/// <summary>
		/// If should detect mouse inputs
		/// </summary>
		bool useMouse = false;
		/// <summary>
		/// The type of mouse key to detect
		/// </summary>
		BalisongEngineFramework::MouseCode shootMouseCode = BalisongEngineFramework::MouseCode::UNKNOWN;

		/// <summary>
		/// If should keep shooting when holding down the key
		/// </summary>
		bool holdFiring = true;

		/// <summary>
		/// If should shoot as soon as the cooldown is done
		/// </summary>
		bool autoFire = false;

		// ===============================================================================

		/// <summary>
		/// The prefab name to look for when shooting
		/// </summary>
		std::string prefabName = "Bullet";
		/// <summary>
		/// The prefab name to look for to have shooting visual effect
		/// </summary>
		std::string muzzlePrefabName = "Muzzle";

		/// <summary>
		/// The spawn point for shooting
		/// </summary>
		TransformComponent* firepoint = nullptr;
		/// <summary>
		/// The local direction based on the firepoint transform
		/// </summary>
		glm::vec2 firepointDir = { 0,1 };
		/// <summary>
		/// The offset angles to add when using the firepoint direction
		/// </summary>
		float angleOffset = 0;
		/// <summary>
		/// The random offset angles to add to the projectile direction
		/// </summary>
		glm::vec2 inaccuracyRange = { -15,15 };
		/// <summary>
		/// The amount of translation to add in the opposite direction of the firepoint direction after shooting
		/// </summary>
		glm::vec2 recoilRange = { .15f,.25f };

		/// <summary>
		/// The amount to translate per second for the projectile
		/// </summary>
		float speed = 2;
		/// <summary>
		/// The seconds before the projectile is destroyed
		/// </summary>
		float lifetime = -1; // infinite

		/// <summary>
		/// The random amount of seconds between allowing shooting
		/// </summary>
		glm::vec2 cooldownRange = { 1,2 };

		// ===============================================================================
		
		/// <summary>
		/// Invoked when shooting
		/// </summary>
		BalisongEngineFramework::ActionEvent<> ShootEvent;

		// ===============================================================================
		
		/// <summary>
		/// The target reference for auto firing to work
		/// </summary>
		BalisongEngineOCM::GameObjectRef targetRef;

		// ===============================================================================
		
	private:

		void Shoot();
		void Muzzle();

		float GetRandom(glm::vec2 range);

		TimerComponent* cooldownTimerComponent = nullptr;
		void RandomizeCooldown();
	};

}
}
