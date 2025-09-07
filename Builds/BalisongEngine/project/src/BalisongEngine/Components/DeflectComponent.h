#pragma once
#include "BaseComponent.h"
#include <vector>
#include <glm/glm.hpp>
#include "ActionEvent.h"

// ================================================================================

namespace BalisongEngine{
namespace BalisongEngineComponents
{
	/// <summary>
	/// The component to change a collider's moving direction to its facing direction
	/// </summary>
	class DeflectComponent : public BaseComponent
	{
	public:

		/// <summary>
		/// ctor
		/// </summary>
		/// <param name="go"></param>
		/// <param name="comp_name"></param>
		DeflectComponent(BalisongEngineOCM::GameObject* go, const std::string& comp_name = "[DeflectComponent]");
		~DeflectComponent();

		void OnCollisionEnter(BalisongEngineOCM::GameObject* other) override;

		// ================================================================================
		
		/// <summary>
		/// The tags to detect, leave empty to detect all tags
		/// </summary>
		std::vector<std::string> deflectTags = { "EnemyBullet" };
		/// <summary>
		/// Checks if the tag is in the deflectTags list
		/// </summary>
		/// <param name="tag"></param>
		/// <returns></returns>
		bool IsTagValid(std::string tag);
		
		/// <summary>
		/// The tag to change the collider's tag to when deflected
		/// </summary>
		std::string convertTag = "PlayerBullet";
		
		/// <summary>
		/// The local direction for deflection, based on the TransformComponent
		/// </summary>
		glm::vec2 facingDir = { 0,1 };

		/// <summary>
		/// The minimum dot product for a deflection to be successful. From -1 to 1. 0 means 180 degrees to deflect
		/// </summary>
		float minDeflectDot = -.2f;

		/// <summary>
		/// The random amount to move in the opposite facing direction after deflecting
		/// </summary>
		glm::vec2 recoilRange = { .1f,.2f };

		/// <summary>
		/// If should destroy self if failed to deflect
		/// </summary>
		bool destroySelfOnFail = true;
		/// <summary>
		/// If should destroy the collider if failed to deflect
		/// </summary>
		bool destroyOtherOnFail = true;

		/// <summary>
		/// Invoked when a deflect is successful
		/// </summary>
		BalisongEngineFramework::ActionEvent<> DeflectEvent;

		// ================================================================================

	private:

		float GetRandom(glm::vec2 range);

	};

}
}

