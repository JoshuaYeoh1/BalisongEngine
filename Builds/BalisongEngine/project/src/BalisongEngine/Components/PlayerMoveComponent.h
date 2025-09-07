#pragma once
#include "BaseComponent.h"
#include <glm/glm.hpp>

// ===============================================================================

namespace BalisongEngine{
namespace BalisongEngineComponents
{
	class MoveComponent; // forward declare

	// ===============================================================================

	/// <summary>
	/// The component to listen to player key inputs to move the GameObject transform
	/// </summary>
	class PlayerMoveComponent : public BaseComponent
	{
	public:

		/// <summary>
		/// ctor
		/// </summary>
		/// <param name="go"></param>
		/// <param name="comp_name"></param>
		PlayerMoveComponent(BalisongEngineOCM::GameObject* go, const std::string& comp_name = "[PlayerMoveComponent]");
		~PlayerMoveComponent();

		void Update(float dt) override;

		// ===============================================================================

		/// <summary>
		/// Sets the MoveComponent reference to modify, and for the starting speed and direction
		/// </summary>
		/// <param name="move_comp">The MoveComponent</param>
		/// <param name="start_speed">Starting speed</param>
		/// <param name="start_dir">Starting direction</param>
		void Init(MoveComponent* move_comp, float start_speed, glm::vec2 start_dir);

		// ===============================================================================

		/// <summary>
		/// Gets the moveSpeed of the MoveComponent
		/// </summary>
		/// <returns></returns>
		float GetMoveSpeed();
		/// <summary>
		/// Sets the moveSpeed of the MoveComponent
		/// </summary>
		/// <param name="to">To value</param>
		void SetMoveSpeed(float to);
		/// <summary>
		/// Reverts moveSpeed to baseMoveSpeed for the MoveComponent
		/// </summary>
		void RevertMoveSpeed();

	private:

		MoveComponent* moveComponent = nullptr;

		float moveSpeed = 1;
		float baseMoveSpeed = 1;
	};

}
}