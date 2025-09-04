#pragma once
#include <vector>
#include <unordered_map>

namespace BalisongEngine{
namespace BalisongEngineOCM
{
	class GameObject; // forward declare

	// ===============================================================================
	
	/// <summary>
	/// For holding a reference to a list of GameObjects, and checks if any are destroyed to automatically remove them from the list
	/// </summary>
	class GameObjectRefSet
	{
	public:
		
		/// <summary>
		/// ctor
		/// </summary>
		GameObjectRefSet();
		~GameObjectRefSet();

		// ===============================================================================

		/// <summary>
		/// Adds a GameObject reference to the list, and tries to subscribe its destroy event
		/// </summary>
		/// <param name="who"></param>
		void Add(GameObject* who);

		/// <summary>
		/// Removes a GameObject reference from the list, and tries to unsubscribe its destroy event
		/// </summary>
		/// <param name="who"></param>
		/// <param name="unsub"></param>
		void Remove(GameObject* who, bool unsub = true);
		/// <summary>
		/// Removes all GameObject references from the list, and unsubscribes their destroy event
		/// </summary>
		void RemoveAll();
		/// <summary>
		/// Removes any GameObject references in the list that is pointing to nothing
		/// </summary>
		void RemoveNulls();
		
		/// <summary>
		/// Checks if a GameObject reference is currently in the list
		/// </summary>
		/// <param name="who"></param>
		/// <returns></returns>
		bool Contains(GameObject* who);
		/// <summary>
		/// Gets the number of GameObject references in the list
		/// </summary>
		/// <returns></returns>
		int Count();
		/// <summary>
		/// Checks if there are no GameObject references in the list
		/// </summary>
		/// <returns></returns>
		bool IsEmpty();

		// ===============================================================================
		
		/// <summary>
		/// Gets the GameObject reference at an index of the list
		/// </summary>
		/// <param name="i"></param>
		/// <returns></returns>
		GameObject* Get(int i);
		/// <summary>
		/// Gets all GameObject references in the list
		/// </summary>
		/// <returns></returns>
		std::vector<GameObject*> GetAll();

		// ===============================================================================

	private:

		std::vector<GameObject*> refs;

		std::unordered_map<GameObject*, int> destroyEventIdsDict;

		void TrySubDestroyEvent(GameObject* who);
		void TryUnsubDestroyEvent(GameObject* who, bool unsub = true);
		void OnRefDestroyed(GameObject* who);

	};

}}