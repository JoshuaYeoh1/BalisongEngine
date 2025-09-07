#pragma once
#include "BaseScene.h"

// ===============================================================================

namespace BalisongEngine{
namespace BalisongEngineScenes
{
	class InputTestScene : public BaseScene
	{
	public:

		std::string GetName() const override { return "InputTestScene"; }

	protected:

		void OnInitialize() override;
		void OnUpdate(float deltaTime) override;
		void OnRender() override;

		float time = 0;
	};

}
}
