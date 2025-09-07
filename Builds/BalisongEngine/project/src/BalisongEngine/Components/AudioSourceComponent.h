#pragma once
#include "BaseComponent.h"
#include <string>
#include <glm/glm.hpp>
#include <irrKlang.h>

//#include <soloud.h>
//#include <soloud_wav.h>

// ===============================================================================

namespace BalisongEngine{
namespace BalisongEngineComponents
{
	/// <summary>
	/// A component that handles audio playback for a GameObject
	/// </summary>
	class AudioSourceComponent : public BaseComponent
	{
	public:

		/// <summary>
		/// ctor
		/// </summary>
		/// <param name="go"></param>
		/// <param name="comp_name"></param>
		AudioSourceComponent(BalisongEngineOCM::GameObject* go, const std::string& comp_name = "[AudioSourceComponent]");
		~AudioSourceComponent();

		void Awake() override;

		// ===============================================================================
		
		/// <summary>
		/// The file path to the audio asset
		/// </summary>
		std::string path = "../assets/audio/.ogg";

		/// <summary>
		/// If should play automatically
		/// </summary>
		bool playOnAwake = true;
		/// <summary>
		/// If should loop after finishing playback
		/// </summary>
		bool loop = false;
		/// <summary>
		/// If should mute
		/// </summary>
		bool mute = false;

		/// <summary>
		/// The volume from 0 to 1
		/// </summary>
		float volume = 1;
		/// <summary>
		/// The left and right panning from -1 to 1
		/// </summary>
		float stereoPan = 0;
		/// <summary>
		/// The playback speed, normal is 1
		/// </summary>
		float speed = 1;

		/// <summary>
		/// If the volume should change based on distance to camera, and if the stereo pan should change if it is left or right of the camera
		/// </summary>
		bool spatialBlend = true;
		/// <summary>
		/// The distance that will be full volume
		/// </summary>
		float minDistance = 1.75f;
		/// <summary>
		/// The distance that will be no volume
		/// </summary>
		float maxDistance = 3.5f;

		// ===============================================================================

		/// <summary>
		/// Plays the current path
		/// </summary>
		void Play();
		/// <summary>
		/// Sets and plays the current path
		/// </summary>
		/// <param name="path"></param>
		void Play(std::string path);

		/// <summary>
		/// Plays the current path without stopping the previous playback
		/// </summary>
		void PlayOneShot();
		/// <summary>
		/// Sets and plays the current path without stopping the previous playback
		/// </summary>
		/// <param name="path"></param>
		void PlayOneShot(std::string path);

		/// <summary>
		/// Checks if playback is not done
		/// </summary>
		/// <returns></returns>
		bool IsPlaying();
		/// <summary>
		/// Gets the length of the current playback in seconds
		/// </summary>
		/// <returns></returns>
		float GetLength();

		/// <summary>
		/// Stops current playback
		/// </summary>
		void Stop();

		// ===============================================================================
		
		void Update(float dt) override;

		// ===============================================================================

		void OnDestroy() override;

		// ===============================================================================

	private:

		irrklang::ISoundEngine* soundEngine = nullptr;
		irrklang::ISound* currentSound = nullptr;

		void ApplySettings(irrklang::ISound* sound);

		// ===============================================================================

		float spatialVolume = 1;
		float spatialStereoPan = 0;

		void UpdateSpatialVolume(glm::vec2 pos);
		void UpdateSpatialStereoPan(glm::vec2 pos);
	};

}
}

// Old
// SoLoud engine
//SoLoud::Soloud soLoud;
//SoLoud::Wav sample;

//int handle = -1;
