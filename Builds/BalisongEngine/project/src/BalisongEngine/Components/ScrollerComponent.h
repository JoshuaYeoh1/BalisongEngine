#pragma once
#include "BaseComponent.h"
#include <glm/glm.hpp>

// ===============================================================================

namespace BalisongEngine{
namespace BalisongEngineComponents
{
	/// <summary>
	/// The component for scrolling animation, like for rolling the credits
	/// </summary>
	class ScrollerComponent : public BaseComponent
	{
	public:

		/// <summary>
		/// ctor
		/// </summary>
		/// <param name="go"></param>
		/// <param name="comp_name"></param>
		ScrollerComponent(BalisongEngineOCM::GameObject* go, const std::string& comp_name = "[ScrollerComponent]");
		~ScrollerComponent();

		void Awake() override;
		void Update(float dt) override;

		// ===============================================================================

		/// <summary>
		/// The size of the visuals ot get the start and end of it
		/// </summary>
		glm::vec2 size = { 1,1 };
		/// <summary>
		/// The translate amount per second
		/// </summary>
		float speed = .2f;

		/// <summary>
		/// Sets the position back to the start
		/// </summary>
		void Reset();

	};

}
}

