#pragma once
#include "BaseComponent.h"
#include "GameObjectRef.h"
#include <glm\glm.hpp>

// ===============================================================================

namespace BalisongEngine{
namespace BalisongEngineComponents
{
	/// <summary>
	/// The component to calculate a velocity using a GameObject's current and previous positions
	/// </summary>
	class VelocityMeterComponent : public BaseComponent
	{
	public:

		/// <summary>
		/// ctor
		/// </summary>
		/// <param name="go"></param>
		/// <param name="comp_name"></param>
		VelocityMeterComponent(BalisongEngineOCM::GameObject* go, const std::string& comp_name = "[VelocityMeterComponent]");
		~VelocityMeterComponent();

		void Update(float dt) override;

		// ===============================================================================

		/// <summary>
		/// Sets the target reference to observe
		/// </summary>
		/// <param name="to"></param>
		void SetTarget(BalisongEngineOCM::GameObject* to);
		/// <summary>
		/// Gets the current target reference being observed
		/// </summary>
		/// <returns></returns>
		BalisongEngineOCM::GameObjectRef GetTargetRef() const;

		// ===============================================================================

		/// <summary>
		/// Gets the target's move speed and direction combined
		/// </summary>
		/// <returns></returns>
		glm::vec2 GetVelocity() const;
		/// <summary>
		/// Gets the target's move speed
		/// </summary>
		/// <returns></returns>
		float GetMagnitude() const;
		/// <summary>
		/// Gets the target's move direction
		/// </summary>
		/// <returns></returns>
		glm::vec2 GetDirection() const;

		// ===============================================================================
		
		void OnDestroy() override;
		
		// ===============================================================================

	private:

		BalisongEngineOCM::GameObjectRef targetRef;

		glm::vec2 velocity = { 0,0 };
		float magnitude = 0;
		glm::vec2 direction = { 0,1 };

		glm::vec2 prevPos = { 0,0 };
	};

}
}