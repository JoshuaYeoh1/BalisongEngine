#pragma once
#include "BaseScene.h"

// ===============================================================================

namespace BalisongEngine{
namespace BalisongEngineScenes
{
	class TestScene : public BaseScene
	{
	public:

		std::string GetName() const override { return "TestScene"; }

	protected:

		void OnInitialize() override;
		void OnUpdate(float deltaTime) override;
		void OnRender() override;

		float time = 0;
	};

}
}
