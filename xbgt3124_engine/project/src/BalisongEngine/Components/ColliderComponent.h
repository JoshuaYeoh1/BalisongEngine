#pragma once
#include "BaseComponent.h"
#include "GameObjectRefSet.h"
#include <glm/glm.hpp>

// ===============================================================================

namespace BalisongEngine{

	namespace BalisongEngineOCM
	{
		class ColliderManager; // forward declare
	}

namespace BalisongEngineComponents
{
	/// <summary>
	/// The component to detect overlapping, and is meant to be inherited by other collider components that have shape
	/// </summary>
	class ColliderComponent : public BaseComponent
	{
	public:

		/// <summary>
		/// ctor
		/// </summary>
		/// <param name="go"></param>
		/// <param name="comp_name"></param>
		ColliderComponent(BalisongEngineOCM::GameObject* go, const std::string& comp_name = "[ColliderComponent]");
		~ColliderComponent();

		void Awake() override;

		// ===============================================================================

		//bool isTrigger = false;

		/// <summary>
		/// The offset to add to the center of shapes
		/// </summary>
		glm::vec2 offset = { 0,0 };
		/// <summary>
		/// Gets the center of the shape
		/// </summary>
		/// <returns></returns>
		glm::vec2 GetCenter() const;

		/// <summary>
		/// The GameObject tags that can collide with it, leave empty to collide with any tag
		/// </summary>
		std::vector<std::string> collideTags;

		// ===============================================================================
		
		/// <summary>
		/// If gizmo of the collider shape is shown
		/// </summary>
		bool showGizmos = false;
		/// <summary>
		/// The color of the gizmo
		/// </summary>
		glm::vec4 gizmosColor = { 1,1,1,1 };
		/// <summary>
		/// The thickness of the gizmo outlines
		/// </summary>
		float gizmosThickness = .005f;

		// ===============================================================================
		
		void OnDestroy() override;

		// ===============================================================================
		
	protected:

		friend class BalisongEngineOCM::ColliderManager;

		virtual bool IsCollidingWith(ColliderComponent* other) = 0; //{ return false; }

		bool IsTagValid(std::string tag) const;

		void OnCollideWith(BalisongEngineOCM::GameObject* other);

		// ===============================================================================

	private:

		BalisongEngineOCM::GameObjectRefSet currentColliders;
		BalisongEngineOCM::GameObjectRefSet previousColliders;

		// ===============================================================================

		void UpdateCollisions();

		void CheckEnter();
		void CheckStay();
		void CheckExit();

		bool IsColliding();

	};

}
}

