#pragma once
#include <string>
#include <vector>
#include "ActionEvent.h"

// ===============================================================================

namespace BalisongEngine
{
	namespace BalisongEngineOCM
	{
		// DO NOT #include "GameObject.h"
		class GameObject; // forward declare that GameObject class exists.
	}

namespace BalisongEngineComponents
{
	class TransformComponent; // forward declare

	// ===============================================================================

	/// <summary>
	/// The component that all other components inherit from, it is attached to a GameObject and has virtual methods to be overriden
	/// </summary>
	class BaseComponent
	{
	public:

		/// <summary>
		/// Contruct the component and attach to a GameObject, then give it a name or leave it as default
		/// </summary>
		/// <param name="go"></param>
		/// <param name="comp_name"></param>
		BaseComponent(BalisongEngineOCM::GameObject* go, const std::string& comp_name = "[BaseComponent]");
		virtual ~BaseComponent() = 0; // pure virtual

		// ===============================================================================

		/// <summary>
		/// Returns the GameObject that it is attached to
		/// </summary>
		/// <returns></returns>
		BalisongEngineOCM::GameObject* GetGameObject();
		/// <summary>
		/// Returns the TransformComponent of the GameObject that it is attached to
		/// </summary>
		/// <returns></returns>
		TransformComponent* GetTransform();

		// ===============================================================================

		/// <summary>
		/// Runs once when the object is first created or activated
		/// </summary>
		virtual void Awake();
		/// <summary>
		/// Runs after Awake
		/// </summary>
		virtual void Start();
		/// <summary>
		/// Runs every frame
		/// </summary>
		/// <param name="delta_time">The time between frames</param>
		virtual void Update(float delta_time);
		/// <summary>
		/// Renders every frame
		/// </summary>
		virtual void Render();

		// ===============================================================================
		
		/// <summary>
		/// When just overlapped the first collider shape this frame
		/// </summary>
		/// <param name="other"></param>
		virtual void OnCollisionFirstEnter(BalisongEngineOCM::GameObject* other);
		/// <summary>
		/// When just overlapped another collider shape this frame
		/// </summary>
		/// <param name="other"></param>
		virtual void OnCollisionEnter(BalisongEngineOCM::GameObject* other);
		/// <summary>
		/// When overlapping another collider shape every frame
		/// </summary>
		/// <param name="others"></param>
		virtual void OnCollisionStay(std::vector<BalisongEngineOCM::GameObject*> others);
		/// <summary>
		/// When just exited another collider shape this frame
		/// </summary>
		/// <param name="other"></param>
		virtual void OnCollisionExit(BalisongEngineOCM::GameObject* other);
		/// <summary>
		/// When just exited the final collider shape this frame
		/// </summary>
		/// <param name="other"></param>
		virtual void OnCollisionLastExit(BalisongEngineOCM::GameObject* other);

		// ===============================================================================
		
		/// <summary>
		/// Flags component for deletion
		/// </summary>
		void DestroyComponent();
		/// <summary>
		/// Checks if component is flagged for deletion
		/// </summary>
		/// <returns></returns>
		bool ShouldDestroy() const;

		/// <summary>
		/// When marked for destroy, use this for cleanup
		/// </summary>
		virtual void OnDestroyComponent();

		/// <summary>
		/// Invoked when this component is flaggedForDeletion this frame 
		/// </summary>
		BalisongEngineFramework::ActionEvent<BaseComponent*> DestroyComponentEvent;

		/// <summary>
		/// When the GameObject that it is attached to was flaggedForDeletion this frame
		/// </summary>
		virtual void OnDestroy();

		// ===============================================================================

	protected:

		BalisongEngineOCM::GameObject* gameObject = nullptr;
		TransformComponent* transform = nullptr;

		std::string name = "";
		std::string componentName = "";
		std::string bothNames = "";

		bool flaggedForDeletion = false;
	};
}
}
