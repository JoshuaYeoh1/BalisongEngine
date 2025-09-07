#pragma once
#include "BaseComponent.h"

// ====================================================================

namespace BalisongEngine{
namespace BalisongEngineComponents
{
	/// <summary>
	/// The component to rotate the GameObject transform
	/// </summary>
	class SpinComponent : public BaseComponent
	{
	public:

		/// <summary>
		/// ctor
		/// </summary>
		/// <param name="go"></param>
		/// <param name="comp_name"></param>
		SpinComponent(BalisongEngineOCM::GameObject* go, const std::string& comp_name = "[SpinComponent]");
		~SpinComponent();

		void Update(float dt) override;

		/// <summary>
		/// The angles per seconds to rotate
		/// </summary>
		float spinSpeed = 360;

	};

}
}

