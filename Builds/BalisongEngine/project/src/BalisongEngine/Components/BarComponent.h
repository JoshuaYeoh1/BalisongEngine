#pragma once
#include "BaseComponent.h"

// ===============================================================================

namespace BalisongEngine{
namespace BalisongEngineComponents
{
	/// <summary>
	/// A component for testing
	/// </summary>
	class BarComponent : public BaseComponent
	{
	public:

		/// <summary>
		/// ctor
		/// </summary>
		/// <param name="go"></param>
		/// <param name="comp_name"></param>
		BarComponent(BalisongEngineOCM::GameObject* go, const std::string& comp_name = "[BarComponent]");
		~BarComponent();

		void Update(float dt) override;
	};

}
}

