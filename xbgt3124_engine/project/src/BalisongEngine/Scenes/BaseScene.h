#pragma once
#include <string>
#include <vector>

// ===============================================================================

namespace BalisongEngine{

	// for subclasses
	namespace BalisongEngineOCM
	{
		class GameObject; //forward declare
	}
	namespace BalisongEngineComponents
	{
		class TransformComponent; //forward declare
	}

namespace BalisongEngineScenes
{
	/// <summary>
	/// The base class for custom scenes to inherit from. It has virtual methods like Update and Render to override. Used in the SceneStateMachine
	/// </summary>
	class BaseScene
	{
	protected:

		bool isActive = false;

		// ===============================================================================

		// virtual functions that are called by defined functions above
		// to allow subclasses to provide custom logic

		virtual void OnInitialize() = 0;
		virtual void OnActivate() {};
		virtual void OnDeactivate() {};

		// ===============================================================================

		virtual void OnUpdate(float dt) {};
		virtual void OnRender() {};

		// ===============================================================================

	public:

		/// <summary>
		/// Get the name of the Scene
		/// </summary>
		/// <returns>string scene name</returns>
		virtual std::string GetName() const = 0;

		// ===============================================================================

	private:

		// public makes it possible for custom components or scenes to call these functions.
		// will make the game unstable.
		// Restrict these functions to only be callable by SceneStateMachine

		void Initialize();
		void Activate();
		void Deactivate();

		// ===============================================================================

		void Update(float deltaTime);
		void Render();

		// Make the SceneStateMachine class a friend of the class containing these functions.
		// This would allow only SceneStateMachine to access them, 
		// while preventing other objects from doing so

		friend class SceneStateMachine;
	};

}
}
