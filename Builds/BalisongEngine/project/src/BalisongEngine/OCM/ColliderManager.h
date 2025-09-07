#pragma once
#include <string>
#include <set>

// ===============================================================================

namespace BalisongEngine{

	namespace BalisongEngineComponents
	{
		class BaseComponent; // forward declare
		class ColliderComponent; // forward declare
	}

namespace BalisongEngineOCM
{
	/// <summary>
	/// The static class to detect any overlaps between all colliders, and sends event to them
	/// </summary>
	class ColliderManager
	{
	public:

		/// <summary>
		/// ctor not for static class
		/// </summary>
		ColliderManager() = delete;

		// ===============================================================================

		/// <summary>
		/// Add a ColliderComponent reference to the list to check
		/// </summary>
		/// <param name="collider"></param>
		static void Add(BalisongEngineComponents::ColliderComponent* collider);
		/// <summary>
		/// Removes a ColliderComponent reference from the list to not check
		/// </summary>
		/// <param name="collider"></param>
		static void Remove(BalisongEngineComponents::ColliderComponent* collider);

		/// <summary>
		/// Checks every frame if any collider in the list is overlapping, then sends event to them
		/// </summary>
		/// <param name="dt"></param>
		static void Update(float dt);

		/// <summary>
		/// Gets all the ColliderComponent references in the list
		/// </summary>
		/// <returns></returns>
		static std::set<BalisongEngineComponents::ColliderComponent*>& GetAllColliders();

		// ===============================================================================
		
		/// <summary>
		/// Removes all the ColliderComponent references from the list
		/// </summary>
		static void Dispose();

		// ===============================================================================

	private:

		static std::set<BalisongEngineComponents::ColliderComponent*> colliders;

		static void OnComponentDestroyed(BalisongEngineComponents::BaseComponent* comp);
	};
}}
