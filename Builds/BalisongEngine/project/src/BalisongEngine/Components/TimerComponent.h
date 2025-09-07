#pragma once
#include "BaseComponent.h"

// ====================================================================

namespace BalisongEngine{
namespace BalisongEngineComponents
{
	/// <summary>
	/// A component to keep track of a countdown
	/// </summary>
	class TimerComponent : public BaseComponent
	{
	public:

		/// <summary>
		/// ctor
		/// </summary>
		/// <param name="go"></param>
		/// <param name="comp_name"></param>
		TimerComponent(BalisongEngineOCM::GameObject* go, const std::string& comp_name = "[TimerComponent]");
		~TimerComponent();

		void Update(float dt) override;

		// ===============================================================================

		/// <summary>
		/// Toggle the countdown
		/// </summary>
		bool isPaused = false;

		// ===============================================================================

		/// <summary>
		/// Set the countdown
		/// </summary>
		/// <param name="t">To seconds</param>
		void SetTimer(float t);
		/// <summary>
		/// Checks if the countdown is not done yet
		/// </summary>
		/// <returns>bool</returns>
		bool HasTimeLeft();
		/// <summary>
		/// Resets the countdown to 0
		/// </summary>
		void FinishTimer();

		// ===============================================================================

		/// <summary>
		/// Get the progress in value from 0 to 1
		/// </summary>
		/// <param name="max">Relative to this max value</param>
		/// <returns>float from 0 to 1</returns>
		float GetNormalizedTimeLeft(float max);

		// ===============================================================================

	protected:

		float secondsLeft = 0;
	};

}
}

