#pragma once
#include "BaseComponent.h"

// ===============================================================================

namespace BalisongEngine{
namespace BalisongEngineComponents
{
	/// <summary>
	/// The component to make the GameObject's transform follow the mouse position in world space
	/// </summary>
	class FollowMouseComponent : public BaseComponent
	{
	public:

		/// <summary>
		/// ctor
		/// </summary>
		/// <param name="go"></param>
		/// <param name="comp_name"></param>
		FollowMouseComponent(BalisongEngineOCM::GameObject* go, const std::string& comp_name = "[FollowMouseComponent]");
		~FollowMouseComponent();

		void Update(float dt) override;

		// ===============================================================================

		/// <summary>
		/// If should follow the mouse or not
		/// </summary>
		bool isActive = true;
	};

}
}