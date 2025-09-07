#pragma once
#include "BaseComponent.h"
#include <glm/glm.hpp>

// ===============================================================================

namespace BalisongEngine{
namespace BalisongEngineComponents
{
	/// <summary>
	/// The component to randomly transform the GameObject on Awake
	/// </summary>
	class RandomTransformComponent : public BaseComponent
	{
	public:

		/// <summary>
		/// ctor
		/// </summary>
		/// <param name="go"></param>
		/// <param name="comp_name"></param>
		RandomTransformComponent(BalisongEngineOCM::GameObject* go, const std::string& comp_name = "[RandomTransformComponent]");
		~RandomTransformComponent();

		void Start() override;

		// ===============================================================================

		/// <summary>
		/// If should affect the position
		/// </summary>
		bool randomTranslate = false;
		/// <summary>
		/// The multiplier for each axis to affect
		/// </summary>
		glm::vec2 translateAxisMult = { 1,1 };
		/// <summary>
		/// The random offset to add to the position
		/// </summary>
		glm::vec2 translateRange = { -.1f,.1f };

		/// <summary>
		/// If should affect the rotation
		/// </summary>
		bool randomRotate = false;
		/// <summary>
		/// The random offset to add to the rotation in angles
		/// </summary>
		glm::vec2 rotateRange = { -180,180 };

		/// <summary>
		/// If should affect the scale
		/// </summary>
		bool randomScaleMult = false;
		/// <summary>
		/// If all axis should be scaled by the same amount
		/// </summary>
		bool uniformScale = true;
		/// <summary>
		/// The multiplier for each axis to affect
		/// </summary>
		glm::vec2 scaleAxisMult = { 1,1 };
		/// <summary>
		/// The random offset to multiply by the scale
		/// </summary>
		glm::vec2 scaleMultRange = { .9f,1.1f };

		// ===============================================================================

	private:

		void Translate();
		void Rotate();
		void ScaleMult();
	};

}
}