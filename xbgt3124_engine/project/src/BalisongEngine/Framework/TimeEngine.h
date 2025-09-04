#pragma once

// ===============================================================================

namespace BalisongEngine{
namespace BalisongEngineFramework
{
	/// <summary>
	/// The static class to calculate time
	/// </summary>
	class TimeEngine
	{
	public:

		/// <summary>
		/// ctor is not for static class
		/// </summary>
		TimeEngine() = delete;

		/// <summary>
		/// Gets the current time in seconds
		/// </summary>
		/// <returns></returns>
		static float GetTime();
		/// <summary>
		/// Gets the time in seconds between frames
		/// </summary>
		/// <returns></returns>
		static float GetDeltaTime();

		/// <summary>
		/// Synchronizes the frame rate by updating the current time and delta time, until the elapsed time meets or exceeds the specified frame time
		/// </summary>
		/// <param name="frame_time"></param>
		static void ProcessTime(float frame_time);
	};
}}