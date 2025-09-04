#pragma once
#include "BaseComponent.h"
#include "ActionEvent.h"
#include <glm/glm.hpp>

// ===============================================================================

namespace BalisongEngine {
namespace BalisongEngineComponents
{
	class SpriteRendererComponent; // forward declare

	// ===============================================================================

	/// <summary>
	/// The component to detect the mouse interacting with it
	/// </summary>
	class ButtonComponent : public BaseComponent
	{
	public:

		/// <summary>
		/// ctor
		/// </summary>
		/// <param name="go"></param>
		/// <param name="comp_name"></param>
		ButtonComponent(BalisongEngineOCM::GameObject* go, const std::string& comp_name = "[ButtonComponent]");
		~ButtonComponent();

		void Update(float dt) override;

		// ===============================================================================

		/// <summary>
		/// If the button is active
		/// </summary>
		bool isActive = true;

		/// <summary>
		/// Checks if the mouse is in the button
		/// </summary>
		/// <returns></returns>
		bool IsHovering();

		// ===============================================================================

		/// <summary>
		/// Invokes when the mouse just entered the button this frame
		/// </summary>
		BalisongEngineFramework::ActionEvent<> HoverEnterEvent;
		/// <summary>
		/// Invokes when the mouse just exited the button this frame
		/// </summary>
		BalisongEngineFramework::ActionEvent<> HoverExitEvent;
		/// <summary>
		/// Invokes when the mouse just pressed the button this frame
		/// </summary>
		BalisongEngineFramework::ActionEvent<> PressEvent;
		/// <summary>
		/// Invokes when the mouse just released the button this frame
		/// </summary>
		BalisongEngineFramework::ActionEvent<> ReleaseEvent;
		/// <summary>
		/// Invokes when the mouse just released while outside the button this frame
		/// </summary>
		BalisongEngineFramework::ActionEvent<> ReleaseCancelEvent;
		/// <summary>
		/// Invokes when the mouse just changed its active state this frame
		/// </summary>
		BalisongEngineFramework::ActionEvent<bool> ToggleActiveEvent;

		// ===============================================================================
		
		/// <summary>
		/// Sets the button's bounding box size
		/// </summary>
		/// <param name="to"></param>
		void SetButtonSize(glm::vec2 to);
		/// <summary>
		/// Sets the button's bounding box size
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		void SetButtonSize(float x, float y);
		/// <summary>
		/// Gets the button's bounding box size
		/// </summary>
		/// <returns></returns>
		glm::vec2 GetButtonSize() const;
		
		/// <summary>
		/// Sets the button's bounding box center
		/// </summary>
		/// <param name="to"></param>
		void SetButtonOffset(glm::vec2 to);
		/// <summary>
		/// Sets the button's bounding box center
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		void SetButtonOffset(float x, float y);
		/// <summary>
		/// Gets the button's bounding box center
		/// </summary>
		/// <returns></returns>
		glm::vec2 GetButtonOffset() const;
		
		// ===============================================================================

		/// <summary>
		/// Sets the button's target sprite to modify and matches its bounding box size to it
		/// </summary>
		/// <param name="to"></param>
		void SetSprite(SpriteRendererComponent* to);

		// ===============================================================================

		/// <summary>
		/// The color and opacity to change the sprite when hovering
		/// </summary>
		glm::vec4 hoverTint = { .75f,1,1,1 };
		/// <summary>
		/// The color and opacity to change the sprite when pressed
		/// </summary>
		glm::vec4 pressTint = { .5f,.5f,.5f,1 };
		/// <summary>
		/// The color and opacity to change the sprite when inactive
		/// </summary>
		glm::vec4 inactiveTint = { .25f,.25f,.25f,1 };

		// ===============================================================================
		
		/// <summary>
		/// The texture path to change the sprite when hovering
		/// </summary>
		std::string hoverTexture = "";
		/// <summary>
		/// The texture path to change the sprite when pressed
		/// </summary>
		std::string pressTexture = "";
		/// <summary>
		/// The texture path to change the sprite when inactive
		/// </summary>
		std::string inactiveTexture = "";

		// ===============================================================================

	private:

		glm::vec2 buttonSize = { 1,1 };
		glm::vec2 buttonOffset = { 0,0 };

		bool IsInButton(glm::vec2 target_pos);

		bool hasHovered = false;
		bool hasPressed = false;
		bool hasActivated = true;

		// ===============================================================================
		 
		void HoverEnter();
		void HoverExit();
		void Press();
		void Release();
		void ReleaseCancel();
		void ToggleActive(bool toggle);

		// ===============================================================================

		SpriteRendererComponent* sprite = nullptr;

		glm::vec4 defaultTint = { 1,1,1,1 };
		void SetTint(glm::vec4 to);
		void RevertTint();

		std::string defaultTexture = "";
		void SetTexture(std::string to);
		void RevertTexture();
	};

}
}
