#pragma once
#include "BaseComponent.h"
#include "ColliderComponent.h"
#include <glm/glm.hpp>

// ===============================================================================

namespace BalisongEngine{
namespace BalisongEngineComponents
{
	class CircleColliderComponent; // forward declare

	// ===============================================================================

	/// <summary>
	/// The component for AABB (Axis-Aligned Bounding Box) overlapping, and can also overlap circles. It can't be rotated nor scaled with the transform
	/// </summary>
	class BoxColliderComponent : public ColliderComponent
	{
	public:

		/// <summary>
		/// ctor
		/// </summary>
		/// <param name="go"></param>
		/// <param name="comp_name"></param>
		BoxColliderComponent(BalisongEngineOCM::GameObject* go, const std::string& comp_name = "[BoxColliderComponent]");
		~BoxColliderComponent();

		// ===============================================================================

		/// <summary>
		/// The size of the overlap box
		/// </summary>
		glm::vec2 size = { 1,1 };

		// ===============================================================================

		void Render() override;

		// ===============================================================================

	protected:

		friend class CircleColliderComponent;

		glm::vec2 GetBottomLeft() const;
		glm::vec2 GetTopRight() const;

		// ===============================================================================

		bool IsCollidingWith(ColliderComponent* other) override;
		bool IsCollidingWithBox(BoxColliderComponent* other);

	};

}
}

