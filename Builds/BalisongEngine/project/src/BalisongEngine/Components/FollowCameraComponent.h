#pragma once
#include "BaseComponent.h"
#include <glm/glm.hpp>

// ===============================================================================

namespace BalisongEngine{
namespace BalisongEngineComponents
{
	/// <summary>
	/// The component for making the GameObject's transform follow the camera's position
	/// </summary>
	class FollowCameraComponent : public BaseComponent
	{
	public:

		/// <summary>
		/// ctor
		/// </summary>
		/// <param name="go"></param>
		/// <param name="comp_name"></param>
		FollowCameraComponent(BalisongEngineOCM::GameObject* go, const std::string& comp_name = "[FollowCameraComponent]");
		~FollowCameraComponent();

		void Update(float dt) override;

		// ===============================================================================

		/// <summary>
		/// The enum for anchor position on the camera
		/// </summary>
		enum class Anchor
		{
			CENTER,
			TOP,
			BOTTOM,
			LEFT,
			RIGHT,
			TOP_LEFT,
			TOP_RIGHT,
			BOTTOM_LEFT,
			BOTTOM_RIGHT,
		};

		/// <summary>
		/// Which anchor to follow
		/// </summary>
		Anchor anchor = Anchor::CENTER;

		/// <summary>
		/// The offset position starting from the anchor position
		/// </summary>
		glm::vec2 offset = { 1,1 };

		// ===============================================================================

	private:

		glm::vec2 GetAnchor();

		void Follow();
	};

}
}

