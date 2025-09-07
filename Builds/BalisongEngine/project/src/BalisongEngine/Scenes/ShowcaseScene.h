#pragma once
#include "BaseScene.h"

// ===============================================================================

namespace BalisongEngine{
namespace BalisongEngineScenes
{
	class ShowcaseScene : public BaseScene
	{
	public:

		std::string GetName() const override { return "ShowcaseScene"; }

	protected:

		void OnInitialize() override;
		void OnUpdate(float deltaTime) override;

		float time = 0;
	};

}
}
