#pragma once
#include "BaseComponent.h"
#include <glm/glm.hpp>

// ====================================================================

namespace BalisongEngine{
namespace BalisongEngineComponents
{
	/// <summary>
	/// The component to animate the GameObject transform in a sine wave motion
	/// </summary>
	class SineTransformComponent : public BaseComponent
	{
	public:

		/// <summary>
		/// ctor
		/// </summary>
		/// <param name="go"></param>
		/// <param name="comp_name"></param>
		SineTransformComponent(BalisongEngineOCM::GameObject* go, const std::string& comp_name = "[SineTransformComponent]");
		~SineTransformComponent();

		void Update(float dt) override;

		// ===============================================================================

		/// <summary>
		/// Toggle the sine animation for position
		/// </summary>
		bool sinePos = false;
		/// <summary>
		/// The frequency of the sine animation
		/// </summary>
		glm::vec2 posFreq = { 0,0 };
		/// <summary>
		/// The amplitude of the sine animation
		/// </summary>
		glm::vec2 posAmp = { 0,0 };

		// ===============================================================================

		/// <summary>
		/// Toggle the sine animation for rotation
		/// </summary>
		bool sineRot = false;
		/// <summary>
		/// The frequency of the sine animation
		/// </summary>
		float rotFreq = 0;
		/// <summary>
		/// The amplitude of the sine animation
		/// </summary>
		float rotAmp = 0;

		// ===============================================================================

		/// <summary>
		/// Toggle the sine animation for scale
		/// </summary>
		bool sineScale = false;
		/// <summary>
		/// The frequency of the sine animation
		/// </summary>
		float scaleFreq = 0;
		/// <summary>
		/// The amplitude of the sine animation
		/// </summary>
		float scaleAmp = 0;

		// ===============================================================================

		/// <summary>
		/// Reset position to default
		/// </summary>
		void ResetPos();
		/// <summary>
		/// Reset rotation to default
		/// </summary>
		void ResetRot();
		/// <summary>
		/// Reset scale to default
		/// </summary>
		void ResetScale();

		// ===============================================================================

	private:

		glm::vec2 defaultPos = { 0,0 };
		float defaultRot = 0;
		glm::vec2 defaultScale = { 1,1 };

		void RecordDefaults();

		// ===============================================================================

		float time = 0;

		// ===============================================================================

		float Sine(float freq, float mag, float offset = 0);

		void SinePos();
		void SineRot();
		void SineScale();

	};

}
}

