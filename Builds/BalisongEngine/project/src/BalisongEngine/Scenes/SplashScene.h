#pragma once
#include "BaseScene.h"

// ===============================================================================

namespace BalisongEngine{
namespace BalisongEngineScenes
{
	class SplashScene : public BaseScene
	{
	public:

		std::string GetName() const override { return "SplashScene"; }

	protected:

		void OnInitialize() override;
		void OnUpdate(float deltaTime) override;

		float time = 0;
	};

}
}
