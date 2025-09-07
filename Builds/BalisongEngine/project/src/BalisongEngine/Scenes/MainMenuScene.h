#pragma once
#include "BaseScene.h"

// ===============================================================================

namespace BalisongEngine{
namespace BalisongEngineScenes
{
	class MainMenuScene : public BaseScene
	{
	public:

		std::string GetName() const override { return "MainMenuScene"; }

	protected:

		void OnInitialize() override;
		void OnUpdate(float dt) override;

		float time = 0;
	};

}
}
