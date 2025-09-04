#pragma once
#include "BaseComponent.h"
#include "ActionEvent.h"
#include <glm/glm.hpp>

// ===============================================================================

namespace BalisongEngine{
namespace BalisongEngineComponents
{
	/// <summary>
	/// The component for moving the GameObject transform
	/// </summary>
	class MoveComponent : public BaseComponent
	{
	public:

		/// <summary>
		/// ctor
		/// </summary>
		/// <param name="go"></param>
		/// <param name="comp_name"></param>
		MoveComponent(BalisongEngineOCM::GameObject* go, const std::string& comp_name = "[MoveComponent]");
		~MoveComponent();

		void Update(float dt) override;

		// ===============================================================================

		/// <summary>
		/// Sets the translate amount per second
		/// </summary>
		/// <param name="to">To value</param>
		void SetSpeed(float to);
		/// <summary>
		/// Gets the translate amount per second
		/// </summary>
		/// <returns>float speed</returns>
		float GetSpeed() const;

		// ===============================================================================

		/// <summary>
		/// Sets and normalizes the direction of moving
		/// </summary>
		/// <param name="dir">To value</param>
		void SetDirection(glm::vec2 to);
		/// <summary>
		/// Gets the direction of moving
		/// </summary>
		/// <returns>vec2 direction</returns>
		glm::vec2 GetDirection() const;

		// ===============================================================================
		
		/// <summary>
		/// Gets the speed and direction combined
		/// </summary>
		/// <returns>vec2 velocity</returns>
		glm::vec2 GetVelocity() const;
		
		// ===============================================================================
		
		/// <summary>
		/// If the rotation should look at the moving direction
		/// </summary>
		bool faceMoveDirection = false;
		/// <summary>
		/// The rotation offset to add when facing the moving direction
		/// </summary>
		float angleOffset = 0;

		// ===============================================================================
		
		/// <summary>
		/// Invoked when just moving or stopping this frame
		/// </summary>
		BalisongEngineFramework::ActionEvent<bool> MoveToggledEvent;

		// ===============================================================================

	private:

		float speed = 1;
		glm::vec2 direction = { 0,1 };
		glm::vec2 velocity = { 0,0 };

		void TryToggleMoveEvent();
		bool hasMoved = false;
	};

}
}