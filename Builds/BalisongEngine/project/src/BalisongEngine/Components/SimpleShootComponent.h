#pragma once
#include "BaseComponent.h"
#include "Input.h" // Include to access the KeyCode enum members

// ====================================================================

namespace BalisongEngine{
namespace BalisongEngineComponents
{
	class MoveComponent; // forward declare
	class TimerComponent; // forward declare

	// ===============================================================================

	/// <summary>
	/// The component to create GameObjects as projectiles to shoot
	/// </summary>
	class SimpleShootComponent : public BaseComponent
	{
	public:

		/// <summary>
		/// ctor
		/// </summary>
		/// <param name="go"></param>
		/// <param name="comp_name"></param>
		SimpleShootComponent(BalisongEngineOCM::GameObject* go, const std::string& comp_name = "[SimpleShootComponent]");
		~SimpleShootComponent();

		void Update(float dt) override;

		// ===============================================================================

		/// <summary>
		/// The KeyCode for shooting
		/// </summary>
		BalisongEngineFramework::KeyCode shootKeycode = BalisongEngineFramework::KeyCode::SPACE;

		// ===============================================================================

		/// <summary>
		/// The cooldown between shots
		/// </summary>
		float shootCooldown = .3f;
		/// <summary>
		/// The TimerComponent for the cooldown timer
		/// </summary>
		TimerComponent* cooldownTimerComponent = nullptr;

		// ===============================================================================

		/// <summary>
		/// The MoveComponent of the shooter
		/// </summary>
		MoveComponent* moveComponent = nullptr;

		/// <summary>
		/// The scale of the projectile
		/// </summary>
		float projectileScale = .2f;
		/// <summary>
		/// The speed of the projectile
		/// </summary>
		float projectileSpeed = 5;
		/// <summary>
		/// The texture path of the projectile
		/// </summary>
		std::string projectileTexturePath = "../assets/";
		/// <summary>
		/// The lifetime of the projectile
		/// </summary>
		float projectileLifetime = .5f;

		// ===============================================================================

		/// <summary>
		/// The method to spawn and setup the projectile
		/// </summary>
		/// <param name="projPos">Projectile spawn position</param>
		/// <param name="projScale">Projectile scale</param>
		/// <param name="projSpeed">Projectile speed</param>
		/// <param name="projDir">Projectile direction</param>
		/// <param name="projTexturePath">Projectile texture path</param>
		/// <param name="projLifetime">Projectile lifetime</param>
		void Shoot(glm::vec2 projPos = {0,0}, float projScale = .2, float projSpeed = 5, glm::vec2 projDir = {0,1}, std::string projTexturePath = "../assets/", float projLifetime = .5);
		/// <summary>
		/// The method to spawn and setup the projectile
		/// </summary>
		/// <param name="projPos"></param>
		/// <param name="projDir"></param>
		void Shoot(glm::vec2 projPos = {0,0}, glm::vec2 projDir = {0,1});

	};

}
}
