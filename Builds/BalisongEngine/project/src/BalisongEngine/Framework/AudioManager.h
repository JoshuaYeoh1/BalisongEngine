#pragma once
#include <string>
#include <glm/glm.hpp>
#include "Random.h"
#include <unordered_map>

// ===============================================================================

namespace BalisongEngine {

	namespace BalisongEngineComponents
	{
		class AudioSourceComponent; // forward declare
	}

namespace BalisongEngineFramework
{
	/// <summary>
	/// Contains the preset properties for finding, setting up, and playing an audio file
	/// </summary>
	struct Audio
	{
		/// <summary>
		/// The name to look for for this audio
		/// </summary>
		std::string name = "";
		/// <summary>
		/// Checks if the name is empty
		/// </summary>
		/// <returns></returns>
		bool IsEmpty() const { return name.empty(); }

		/// <summary>
		/// The first part of the file path
		/// </summary>
		std::string pathPrefix = "../assets/audio/";
		/// <summary>
		/// The last part of the file path
		/// </summary>
		std::string pathSuffix = ".ogg";
		/// <summary>
		/// The number of random file paths for random audio
		/// </summary>
		int paths = 1;

		/// <summary>
		/// Combines and gets the randomized full file path to the audio file
		/// </summary>
		/// <returns></returns>
		std::string GetPath() const
		{
			if (paths > 1)
			{
				int i = Random::Range(1, paths+1);
				return pathPrefix + std::to_string(i) + pathSuffix;
			}
			return pathPrefix + pathSuffix;
		}

		/// <summary>
		/// The random volume to play
		/// </summary>
		glm::vec2 volumeRange = { 1,1 };
		/// <summary>
		/// Gets the randomized volume
		/// </summary>
		/// <returns></returns>
		float GetVolume() const { return Random::Range(volumeRange.x, volumeRange.y); }

		/// <summary>
		/// The left right stereo pan value to play
		/// </summary>
		glm::vec2 stereoPanRange = { 0,0 };
		/// <summary>
		/// Gets the randomized stereo pan
		/// </summary>
		/// <returns></returns>
		float GetStereoPan() const { return Random::Range(stereoPanRange.x, stereoPanRange.y); }

		/// <summary>
		/// The speed and pitch to play
		/// </summary>
		glm::vec2 speedRange = { .8f,1.2f };
		/// <summary>
		/// Gets the randomized speed
		/// </summary>
		/// <returns></returns>
		float GetSpeed() const { return Random::Range(speedRange.x, speedRange.y); }

		/// <summary>
		/// If should modify volume and stereo pan based on Audio source's distance to the camera
		/// </summary>
		bool spatialBlend = true;
		/// <summary>
		/// The range to play full volume
		/// </summary>
		float minDistance = 1.75f;
		/// <summary>
		/// The range to play at zero volume
		/// </summary>
		float maxDistance = 3.5f;
	};

	// ===============================================================================

	/// <summary>
	/// The static manager to store a list of audio lookup names and their preset properties, for spawning a temporary AudioSourceComponent anywhere for sound effects
	/// </summary>
	class AudioManager
	{
	public:

		/// <summary>
		/// Adds an audio preset to the list
		/// </summary>
		/// <param name="new_audio"></param>
		static void AddAudio(const Audio& new_audio);
		/// <summary>
		/// Removes an audio preset from the list
		/// </summary>
		/// <param name="audio_name"></param>
		static void RemoveAudio(const std::string& audio_name);
		/// <summary>
		/// Goes through the list to find the audio preset's name, then returns the audio preset
		/// </summary>
		/// <param name="audio_name"></param>
		/// <returns></returns>
		static Audio* GetAudio(const std::string& audio_name);

		/// <summary>
		/// Finds the audio preset, then spawns a temporary GameObject anywhere with an AudioSourceComponent to play. It will be destroyed after finished playing the audio 
		/// </summary>
		/// <param name="audio_name"></param>
		/// <param name="pos"></param>
		/// <returns></returns>
		static BalisongEngineComponents::AudioSourceComponent* Play(const std::string& audio_name, const glm::vec2& pos = {0,0});

		// ===============================================================================

	private:

		static std::unordered_map<std::string, Audio> audios;

	};

}
}

