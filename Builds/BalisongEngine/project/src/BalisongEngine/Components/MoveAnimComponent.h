#pragma once
#include "BaseComponent.h"

// ===============================================================================

namespace BalisongEngine{
namespace BalisongEngineComponents
{
	class MoveComponent; // forward declare
	class AnimatorComponent; // forward declare

	// ===============================================================================

	/// <summary>
	/// The component to set the animation based on moving or stopping
	/// </summary>
	class MoveAnimComponent : public BaseComponent
	{
	public:

		/// <summary>
		/// ctor
		/// </summary>
		/// <param name="go"></param>
		/// <param name="comp_name"></param>
		MoveAnimComponent(BalisongEngineOCM::GameObject* go, const std::string& comp_name = "[MoveAnimComponent]");
		~MoveAnimComponent();

		// ===============================================================================

		/// <summary>
		/// Sets the references for the MoveComponent to check and AnimatorComponent to modify
		/// </summary>
		/// <param name="move_comp"></param>
		/// <param name="anim_comp"></param>
		void Init(MoveComponent* move_comp, AnimatorComponent* anim_comp);

		/// <summary>
		/// The animation name to look for when not moving
		/// </summary>
		std::string idleAnimName = "Idle";
		/// <summary>
		/// The animation name to look for when moving
		/// </summary>
		std::string moveAnimName = "Move";

		// ===============================================================================
		
		void OnDestroyComponent() override;

		// ===============================================================================

	private:

		MoveComponent* moveComp = nullptr;
		AnimatorComponent* animComp = nullptr;

		void OnMoveToggled(bool toggle);
		int OnMoveToggled_id = 0;
	};

}
}