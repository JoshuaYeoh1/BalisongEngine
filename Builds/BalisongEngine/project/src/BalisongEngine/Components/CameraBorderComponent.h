#pragma once
#include "BaseComponent.h"

// ===============================================================================

namespace BalisongEngine{
namespace BalisongEngineComponents
{
	/// <summary>
	/// The component to stop the position from going outside the camera edges
	/// </summary>
	class CameraBorderComponent : public BaseComponent
	{
	public:

		/// <summary>
		/// ctor
		/// </summary>
		/// <param name="go"></param>
		/// <param name="comp_name"></param>
		CameraBorderComponent(BalisongEngineOCM::GameObject* go, const std::string& comp_name = "[CameraBorderComponent]");
		~CameraBorderComponent();

		void Update(float dt) override;

		// ===============================================================================

		/// <summary>
		/// If the constrain is active
		/// </summary>
		bool isActive = true;

		/// <summary>
		/// The spacing to offset by the edges
		/// </summary>
		float expandOffset = -.1f;
	};

}
}