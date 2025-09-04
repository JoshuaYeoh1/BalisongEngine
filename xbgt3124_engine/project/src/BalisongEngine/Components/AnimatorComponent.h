#pragma once
#include "BaseComponent.h"
#include "ActionEvent.h"
#include <unordered_map>

// ===============================================================================

namespace BalisongEngine{
namespace BalisongEngineComponents
{
	/// <summary>
	/// For setting up presets of animation data
	/// </summary>
	struct Anim
	{
		/// <summary>
		/// The name that will be searched for
		/// </summary>
		std::string animName = "";
		/// <summary>
		/// Checks if the name is empty
		/// </summary>
		/// <returns></returns>
		bool IsEmpty() const { return animName.empty(); }

		/// <summary>
		/// The first part of the file path
		/// </summary>
		std::string pathPrefix = "../assets/";
		/// <summary>
		/// the last part of the file path
		/// </summary>
		std::string pathSuffix = ".png";

		/// <summary>
		/// How many file paths to go through when animating
		/// </summary>
		int frames = 1;
		/// <summary>
		/// The frames per second
		/// </summary>
		int fps = 24;
		/// <summary>
		/// Gets how long a single frame lasts
		/// </summary>
		/// <returns></returns>
		float GetFrameDuration() const { return fps!=0 ? (1.0f/fps) : 0; } // IT MUST BE 1.0f, NOT 1
		/// <summary>
		/// Gets how long the whole animation lasts
		/// </summary>
		/// <returns></returns>
		float GetDuration() const { return GetFrameDuration() * frames; }
		/// <summary>
		/// Gets the last frame index
		/// </summary>
		/// <returns></returns>
		int GetLastIndex() const { return frames-1; }

		/// <summary>
		/// If the animation should loop or not
		/// </summary>
		bool loop = true;

		/// <summary>
		/// The next animation name to look for after this is done
		/// </summary>
		std::string nextAnimName = "";
		/// <summary>
		/// Checks if the next animation is empty
		/// </summary>
		/// <returns></returns>
		bool HasNextAnim() const { return !nextAnimName.empty(); }

		/// <summary>
		/// Destroys the game object that the animator is on after the animation is done
		/// </summary>
		bool destroyOnFinish = false;
	};

	// ===============================================================================

	class SpriteRendererComponent; // forward declare

	// ===============================================================================

	/// <summary>
	/// This component is for storing a list of animations, finding animation names, going through all frames and changing the SpriteRenderer texture to play the animation
	/// </summary>
	class AnimatorComponent : public BaseComponent
	{
	public:

		/// <summary>
		/// ctor
		/// </summary>
		/// <param name="go"></param>
		/// <param name="comp_name"></param>
		AnimatorComponent(BalisongEngineOCM::GameObject* go, const std::string& comp_name = "[AnimatorComponent]");
		~AnimatorComponent();

		void Update(float dt) override;

		// ===============================================================================
		
		/// <summary>
		/// The current SpriteRendererComponent to control
		/// </summary>
		SpriteRendererComponent* sprite = nullptr;

		// ===============================================================================
		
		/// <summary>
		/// Adds a new animation to the list
		/// </summary>
		/// <param name="new_anim"></param>
		void AddAnim(Anim new_anim);
		/// <summary>
		/// Looks for the animation name and removes the animation from the list
		/// </summary>
		/// <param name="anim_name"></param>
		void RemoveAnim(const std::string& anim_name);

		/// <summary>
		/// Looks for the animation name and plays the animation
		/// </summary>
		/// <param name="anim_name"></param>
		void SetAnim(const std::string& anim_name);
		/// <summary>
		/// Looks for the animation name and returns the animation
		/// </summary>
		/// <param name="anim_name"></param>
		/// <returns></returns>
		Anim* GetAnim(const std::string& anim_name);
		/// <summary>
		/// Returns the current animation
		/// </summary>
		/// <returns></returns>
		Anim* GetCurrentAnim();

		/// <summary>
		/// Looks for the animation name and see if it exists in the list
		/// </summary>
		/// <param name="anim_name"></param>
		/// <returns></returns>
		bool HasAnim(const std::string& anim_name);

		// ===============================================================================

		/// <summary>
		/// If the current animation is paused or not
		/// </summary>
		bool isPaused = false;

		// ===============================================================================
		
		/// <summary>
		/// Invokes after the current animation is done
		/// </summary>
		BalisongEngineFramework::ActionEvent<Anim*> AnimFinishedEvent;

		// ===============================================================================

	private:

		std::unordered_map<std::string, Anim> anims;

		Anim* currentAnim = nullptr;
		int currentFrameIndex = 0;
		float animTimer = 0;
		
		void TryFinishAnim();
	};

}
}