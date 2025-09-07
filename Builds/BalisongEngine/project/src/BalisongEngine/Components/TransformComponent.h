#pragma once
#include "BaseComponent.h"
#include <glm/glm.hpp>
#include <vector>

// ====================================================================

namespace BalisongEngine{
namespace BalisongEngineComponents
{
	/// <summary>
	/// The component to store values like position, rotation, and scale. It can also do parenting for hierarchical transformations
	/// </summary>
	class TransformComponent : public BaseComponent
	{
	public:

		/// <summary>
		/// ctor
		/// </summary>
		/// <param name="go"></param>
		/// <param name="comp_name"></param>
		TransformComponent(BalisongEngineOCM::GameObject* go, const std::string& comp_name = "[TransformComponent]");
		~TransformComponent();
 
		// ===============================================================================

		/// <summary>
		/// Get the localPosition
		/// </summary>
		/// <returns>vec2 localPosition</returns>
		glm::vec2 GetLocalPosition() const;
		
		/// <summary>
		/// Set the localPosition
		/// </summary>
		/// <param name="to">To position</param>
		void SetLocalPosition(glm::vec2 to);
		/// <summary>
		/// Set the localPosition
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		void SetLocalPosition(float x, float y);

		/// <summary>
		/// Add to the localPosition
		/// </summary>
		/// <param name="by">Amount to add</param>
		void TranslateLocal(glm::vec2 by);
		/// <summary>
		/// Add to the localPosition
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		void TranslateLocal(float x, float y);

		// ===============================================================================

		/// <summary>
		/// Get the worldPosition
		/// </summary>
		/// <returns>vec2 worldPosition</returns>
		glm::vec2 GetWorldPosition() const;

		/// <summary>
		/// Set the worldPosition
		/// </summary>
		/// <param name="to">To position</param>
		void SetWorldPosition(glm::vec2 to);
		/// <summary>
		/// Set the worldPosition
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		void SetWorldPosition(float x, float y);

		// ===============================================================================

		/// <summary>
		/// Get the localRotation
		/// </summary>
		/// <returns>float angle</returns>
		float GetLocalRotation() const;

		/// <summary>
		/// Set the localRotation
		/// </summary>
		/// <param name="angle">To angle</param>
		void SetLocalRotation(float angle);

		/// <summary>
		/// Add to the localRotation
		/// </summary>
		/// <param name="by">Angle to add</param>
		void RotateLocal(float by);

		// ===============================================================================

		/// <summary>
		/// Get the worldRotation
		/// </summary>
		/// <returns>float worldAngles</returns>
		float GetWorldRotation() const;

		/// <summary>
		/// Set the worldRotation
		/// </summary>
		/// <param name="angle">To angle</param>
		void SetWorldRotation(float angle);

		// ===============================================================================

		/// <summary>
		/// Get the localScale
		/// </summary>
		/// <returns>vec2 localScale</returns>
		glm::vec2 GetLocalScale() const;

		/// <summary>
		/// Set the localScale
		/// </summary>
		/// <param name="to">To scale</param>
		void SetLocalScale(glm::vec2 to);
		/// <summary>
		/// Set the localScale
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		void SetLocalScale(float x, float y);
		/// <summary>
		/// Set the localScale
		/// </summary>
		/// <param name="to"></param>
		void SetLocalScale(float to);
		
		/// <summary>
		/// Add to the localScale
		/// </summary>
		/// <param name="by">Scale to add</param>
		void AddLocalScale(glm::vec2 by);
		/// <summary>
		/// Add to the localScale
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		void AddLocalScale(float x, float y);
		/// <summary>
		/// Add to the localScale
		/// </summary>
		/// <param name="by"></param>
		void AddLocalScale(float by);
		
		/// <summary>
		/// Multiply with the localScale
		/// </summary>
		/// <param name="by">Scale to multiple by</param>
		void LocalScaleMult(glm::vec2 by);
		/// <summary>
		/// Multiply with the localScale
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		void LocalScaleMult(float x, float y);
		/// <summary>
		/// Multiply with the localScale
		/// </summary>
		/// <param name="by"></param>
		void LocalScaleMult(float by);

		// ===============================================================================

		/// <summary>
		/// Get the worldScale
		/// </summary>
		/// <returns>vec2 worldScale</returns>
		glm::vec2 GetWorldScale() const;

		/// <summary>
		/// Set the worldScale
		/// </summary>
		/// <param name="to">To scale</param>
		void SetWorldScale(glm::vec2 to);
		/// <summary>
		/// Set the worldScale
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		void SetWorldScale(float x, float y);
		/// <summary>
		/// Set the worldScale
		/// </summary>
		/// <param name="to"></param>
		void SetWorldScale(float to);

		// ===============================================================================

		/// <summary>
		/// Combines the translation, rotation, and scaling. If got parent, it multiplies the parent's model matrix with its own one for hierarchical transformation
		/// </summary>
		/// <returns>the model transformation matrix</returns>
		glm::mat4 GetModelMatrix() const;

		/// <summary>
		/// Get the parent
		/// </summary>
		/// <returns>The parent's TransformComponent</returns>
		TransformComponent* GetParent() const;
		/// <summary>
		/// Set the parent
		/// </summary>
		/// <param name="target">To parent's TransformComponent</param>
		void SetParent(TransformComponent* target);
		
		/// <summary>
		/// Adds a TransformComponent reference to the list
		/// </summary>
		/// <param name="child"></param>
		void AddChild(TransformComponent* child);
		/// <summary>
		/// Removes a TransformComponent reference from the list
		/// </summary>
		/// <param name="child"></param>
		void RemoveChild(TransformComponent* child);
		/// <summary>
		/// Destroys the GameObjects of all the TransformComponent references in the list
		/// </summary>
		void DeleteChildren();

		// ===============================================================================

		/// <summary>
		/// Get the positive Y local direction
		/// </summary>
		/// <returns>vec3 direction</returns>
		glm::vec2 GetLocalUp() const;
		/// <summary>
		/// Get the negative Y local direction
		/// </summary>
		/// <returns>vec3 direction</returns>
		glm::vec2 GetLocalDown() const;
		/// <summary>
		/// Get the positive X local direction
		/// </summary>
		/// <returns>vec3 direction</returns>
		glm::vec2 GetLocalRight() const;
		/// <summary>
		/// Get the negative X local direction
		/// </summary>
		/// <returns>vec3 direction</returns>
		glm::vec2 GetLocalLeft() const;

		// ===============================================================================
		
		/// <summary>
		/// Get Direction to target position
		/// </summary>
		/// <param name="pos"></param>
		/// <returns></returns>
		glm::vec2 GetDirection(glm::vec2 to) const;

		/// <summary>
		/// Set rotation to face target direction with an offset
		/// </summary>
		/// <param name="dir"></param>
		/// <param name="angle_offset"></param>
		void FaceDirection(glm::vec2 to, float angle_offset);

		/// <summary>
		/// Set rotation to target position with an offset
		/// </summary>
		/// <param name="pos"></param>
		/// <param name="angle_offset"></param>
		void LookAt(glm::vec2 pos, float angle_offset);

		// ===============================================================================

		/// <summary>
		/// Gets the distance between its world position and another position
		/// </summary>
		/// <param name="to"></param>
		/// <returns></returns>
		float GetDistance(glm::vec2 to) const;

		// ===============================================================================

		/// <summary>
		/// Gets the position relative from this transform
		/// </summary>
		/// <param name="pos"></param>
		/// <returns></returns>
		glm::vec2 TransformPoint(glm::vec2 pos) const;
		/// <summary>
		/// Gets the direction relative from this transform
		/// </summary>
		/// <param name="dir"></param>
		/// <returns></returns>
		glm::vec2 TransformDirection(glm::vec2 dir) const;

		// ===============================================================================
		
		void OnDestroyComponent() override;

		// ===============================================================================

	protected:

		glm::vec2 localPosition = { 0,0 };
		float localRotation = 0;
		glm::vec2 localScale = { 1,1 };

		TransformComponent* parent = nullptr;
		std::vector<TransformComponent*> children;
	};

}
}

