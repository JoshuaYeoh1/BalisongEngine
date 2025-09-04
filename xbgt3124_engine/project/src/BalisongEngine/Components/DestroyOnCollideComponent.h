#pragma once
#include "BaseComponent.h"
#include <vector>

// ================================================================================

namespace BalisongEngine{
namespace BalisongEngineComponents
{
	/// <summary>
	/// The component to destroy the GameObject on collision enter with another collider
	/// </summary>
	class DestroyOnCollideComponent : public BaseComponent
	{
	public:

		/// <summary>
		/// ctor
		/// </summary>
		/// <param name="go"></param>
		/// <param name="comp_name"></param>
		DestroyOnCollideComponent(BalisongEngineOCM::GameObject* go, const std::string& comp_name = "[DestroyOnCollideComponent]");
		~DestroyOnCollideComponent();

		void OnCollisionEnter(BalisongEngineOCM::GameObject* other) override;

		// ================================================================================
		
		/// <summary>
		/// The tags to detect when on collision enter. Leave empty to allow all tags
		/// </summary>
		std::vector<std::string> validTags;
		/// <summary>
		/// If the tag is included in the validTags list
		/// </summary>
		/// <param name="tag"></param>
		/// <returns></returns>
		bool IsTagValid(std::string tag);

		/// <summary>
		/// If should destroy its GameObject on collision
		/// </summary>
		bool destroySelf = true;
		/// <summary>
		/// If should destroy the collider on collision
		/// </summary>
		bool destroyOther = true;
	};

}
}

