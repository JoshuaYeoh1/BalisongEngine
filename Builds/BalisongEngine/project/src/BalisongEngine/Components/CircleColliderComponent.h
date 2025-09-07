#pragma once
#include "BaseComponent.h"
#include "ColliderComponent.h"

// ===============================================================================

namespace BalisongEngine{
namespace BalisongEngineComponents
{
	class BoxColliderComponent; // forward declare

	// ===============================================================================

	/// <summary>
	/// The component for radii overlapping, and can also overlap AABB. It can't be scaled with the transform
	/// </summary>
	class CircleColliderComponent : public ColliderComponent
	{
	public:

		/// <summary>
		/// ctor
		/// </summary>
		/// <param name="go"></param>
		/// <param name="comp_name"></param>
		CircleColliderComponent(BalisongEngineOCM::GameObject* go, const std::string& comp_name = "[CircleColliderComponent]");
		~CircleColliderComponent();

		// ===============================================================================
		
		/// <summary>
		/// The range of the circle
		/// </summary>
		float radius = .5f;

		// ===============================================================================

		void Render() override;

		// ===============================================================================

	protected:

		friend class BoxColliderComponent;

		bool IsCollidingWith(ColliderComponent* other) override;
		bool IsCollidingWithCircle(CircleColliderComponent* other);
		bool IsCollidingWithBox(BoxColliderComponent* other);

	};

}
}

