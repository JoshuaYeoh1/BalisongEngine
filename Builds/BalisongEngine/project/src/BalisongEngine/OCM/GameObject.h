#pragma once
#include <glm/vec2.hpp>
#include <string>
#include <vector>
#include "ActionEvent.h"
#include <iostream>

// ===============================================================================

namespace BalisongEngine
{
	namespace BalisongEngineComponents
	{
		class BaseComponent; // forward declare
		class TransformComponent; // forward declare
	}

namespace BalisongEngineOCM
{
	/// <summary>
	/// The object to hold components, and sends events to them
	/// </summary>
	class GameObject
	{
	public:

		/// <summary>
		/// Ctor with custom name
		/// </summary>
		/// <param name="custom_name"></param>
		GameObject(const std::string& custom_name);
		/// <summary>
		/// Ctor with default name ([GO] NewObject)
		/// </summary>
		GameObject();
		~GameObject();

		// ===============================================================================

		/// <summary>
		/// The name of the GameObject
		/// </summary>
		std::string name = "[GO] New Object";
		/// <summary>
		/// The tag of the GameObject
		/// </summary>
		std::string tag = "";

		/// <summary>
		/// Gets the TransformComponent for the GameObject
		/// </summary>
		/// <returns>TransformComponent</returns>
		BalisongEngineComponents::TransformComponent* GetTransform();

		// ===============================================================================

		/// <summary>
		/// Adds new component to the GameObject, and checks for no duplicate TransformComponent
		/// </summary>
		/// <typeparam name="T">Any class deriving from BaseComponent</typeparam>
		/// <typeparam name="">BaseComponent</typeparam>
		/// <returns>Class deriving from BaseComponent</returns>
		template <
			typename T,
			typename = typename std::enable_if<std::is_base_of<BalisongEngineComponents::BaseComponent, T>::value>::type
		>
		T* AddComponent()
		{
			// check if TransformComponent already exists
			if (std::is_same<T, BalisongEngineComponents::TransformComponent>::value && transform != nullptr)
			{
				std::cout << name << ": Already got Transform component!\n";
				return nullptr;
			}

			// Create instance of T, expecting that T has a constructor that takes GameObject*
			T* new_comp = new T(this);
			// Add the instance of T to componentsToAdd
			componentsJustAdded.push_back(new_comp);
			// Also add it to components
			components.push_back(new_comp);

			return new_comp;
		}

		// ===============================================================================
		
		/// <summary>
		/// Gets component of the GameObject
		/// </summary>
		/// <typeparam name="T">Any class deriving from BaseComponent</typeparam>
		/// <typeparam name="">BaseComponent</typeparam>
		/// <returns>Class deriving from BaseComponent</returns>
		template <
			typename T,
			typename = typename std::enable_if<std::is_base_of<BalisongEngineComponents::BaseComponent, T>::value>::type
		>
		T* GetComponent()
		{
			// iterate the vector to find component that matches the type.
			for (auto& c : components)
			{
				// find component that matches the type.
				// return the first item found.
				T* tryCast = dynamic_cast<T*>(c);

				if (tryCast != nullptr) return tryCast;
			}
			// if nothing found, return null (0)
			return nullptr;
		};

		// ===============================================================================
		
		/// <summary>
		/// Tries to get a component of the GameObject
		/// </summary>
		template <
			typename T,
			typename = typename std::enable_if<std::is_base_of<BalisongEngineComponents::BaseComponent, T>::value>::type
		>
		bool TryGetComponent(T*& component)
		{
			component = GetComponent<T>();
			return component != nullptr;
		};

		// ===============================================================================

		/// <summary>
		/// Makes sure that GameObject has this component
		/// </summary>
		template <
			typename T,
			typename = typename std::enable_if<std::is_base_of<BalisongEngineComponents::BaseComponent, T>::value>::type
		>
		void EnforceComponent(T*& component)
		{
			if (component) return;
			component = GetComponent<T>();
			if (component) return;
			component = AddComponent<T>();
		};

		// ===============================================================================

		/// <summary>
		/// Goes through all componentsJustAdded and runs their Awake methods
		/// </summary>
		void RunComponentAwake();
		/// <summary>
		/// Goes through all componentsJustAdded and runs their Start methods, then clears all componentsJustAdded
		/// </summary>
		void RunComponentStart();
		/// <summary>
		/// Goes through all components and clears those that are flaggedForDeletion, then runs the Update methods of the remaining
		/// </summary>
		void RunComponentUpdate(float dt);
		/// <summary>
		/// Goes through all components and runs their Render methods
		/// </summary>
		void RunComponentRender();

		// ===============================================================================

		/// <summary>
		/// When just overlapped a collider this frame if haven't previously overlapped
		/// </summary>
		/// <param name="other"></param>
		void OnCollisionFirstEnter(GameObject* other);
		/// <summary>
		/// When just overlapped a collider this frame
		/// </summary>
		/// <param name="other"></param>
		void OnCollisionEnter(GameObject* other);
		/// <summary>
		/// When overlapping colliders every frame
		/// </summary>
		/// <param name="others"></param>
		void OnCollisionStay(std::vector<GameObject*> others);
		/// <summary>
		/// When just exited a collider this frame
		/// </summary>
		/// <param name="other"></param>
		void OnCollisionExit(GameObject* other);
		/// <summary>
		/// When just exited a collider this frame and not overlapping any other colliders
		/// </summary>
		/// <param name="other"></param>
		void OnCollisionLastExit(GameObject* other);		

		// ===============================================================================
		
		/// <summary>
		/// Flags the GameObject for deletion
		/// </summary>
		void Destroy(float delay = 0);
		/// <summary>
		/// Checks if GameObject is flaggedForDeletion
		/// </summary>
		/// <returns>bool</returns>
		bool ShouldDestroy() const;

		/// <summary>
		/// Invoked when GameObject is flaggedForDeletion
		/// </summary>
		BalisongEngineFramework::ActionEvent<GameObject*> DestroyEvent;

		// ===============================================================================

		/// <summary>
		/// Overrides 'new' to use the pool allocator
		/// </summary>
		/// <param name="size">Max number of GameObjects (1024)</param>
		/// <returns></returns>
		static void* operator new(size_t size);

		/// <summary>
		/// Overrides 'delete' to use the pool allocator
		/// </summary>
		/// <param name="ptr"></param>
		/// <param name="size"></param>
		static void operator delete(void* ptr, size_t size);

		// ===============================================================================

	protected:

		BalisongEngineComponents::TransformComponent* transform;

	private:

		std::vector<BalisongEngineComponents::BaseComponent*> components;
		std::vector<BalisongEngineComponents::BaseComponent*> componentsJustAdded;

		void FlagComponentsForDestroy();
		void DeleteFlaggedComponents();

		// ===============================================================================

		bool destroyDelayStarted = false;
		float destroyDelayTimer = 0;

		bool flaggedForDeletion = false;

		void OnDestroy();
	};
}}