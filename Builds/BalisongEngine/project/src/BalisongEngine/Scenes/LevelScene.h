#pragma once
#include "BaseScene.h"
#include <glm/glm.hpp>

// ===============================================================================

namespace BalisongEngine{
namespace BalisongEngineScenes
{
	class LevelScene : public BaseScene
	{
	public:

		std::string GetName() const override { return "LevelScene"; }

	protected:

		void OnInitialize() override;
		void OnUpdate(float dt) override;

		// ===============================================================================

		float time = 0;

		float minTime = 0;
		float maxTime = 60;

		glm::vec2 minSpawnrate = { 2,5 };
		glm::vec2 maxSpawnrate = { .1f,.2f };

		// ===============================================================================

		BalisongEngineOCM::GameObject* player = nullptr;
		void OnPlayerDestroyed(BalisongEngineOCM::GameObject* who);

		float death_time = 0;

		BalisongEngineOCM::GameObject* loseUI = nullptr;
	};

}
}
