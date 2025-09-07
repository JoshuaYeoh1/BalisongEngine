#pragma once
#include <random> // For std::uniform_int_distribution and std::uniform_real_distribution

namespace BalisongEngine {
namespace BalisongEngineFramework
{
	/// <summary>
	/// The static class to generate random numbers
	/// </summary>
	class Random
	{
	public:

		/// <summary>
		/// Gets a random float in a range 
		/// </summary>
		/// <param name="min"></param>
		/// <param name="max"></param>
		/// <returns></returns>
		static float Range(float min, float max);
		/// <summary>
		/// Gets a random integer in a range, exclusive of the maximum value
		/// </summary>
		/// <param name="min"></param>
		/// <param name="max"></param>
		/// <returns></returns>
		static int Range(int min, int max);

		// ===============================================================================

	private:

		/// <summary>
		/// Random device for generating a seed
		/// </summary>
		static std::random_device rd;
		/// <summary>
		/// Mersenne Twister generator for random number generation
		/// </summary>
		static std::mt19937 rng;
	};

}
}

