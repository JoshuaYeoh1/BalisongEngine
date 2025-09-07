#pragma once
#include "BaseScene.h"

// ===============================================================================

namespace BalisongEngine{
namespace BalisongEngineScenes
{
	class CreditsScene : public BaseScene
	{
	public:

		std::string GetName() const override { return "CreditsScene"; }

	protected:

		void OnInitialize() override;
		void OnUpdate(float dt) override;

		float time = 0;
	};

}
}
