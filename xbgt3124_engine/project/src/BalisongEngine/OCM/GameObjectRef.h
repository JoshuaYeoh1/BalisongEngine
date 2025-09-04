#pragma once

namespace BalisongEngine{
namespace BalisongEngineOCM
{
	class GameObject; // forward declare

	// ===============================================================================
	
	/// <summary>
	/// For holding a reference to a GameObject, and checks if it is destroyed to automatically reset the pointer
	/// </summary>
	class GameObjectRef
	{
	public:
		
		/// <summary>
		/// ctor
		/// </summary>
		/// <param name="who"></param>
		GameObjectRef(GameObject* who = nullptr);
		~GameObjectRef();

		// ===============================================================================

		/// <summary>
		/// Sets the reference to a GameObject, and tries to subscribe and unsubscribe its destroy event
		/// </summary>
		/// <param name="to"></param>
		void Set(GameObject* to);
		/// <summary>
		/// Gets the current GameObject reference
		/// </summary>
		/// <returns></returns>
		GameObject* Get() const;
	
		// ===============================================================================

	private:

		GameObject* ref = nullptr;

		void TrySubDestroyEvent();
		void TryUnsubDestroyEvent();
		int destroyEventId = -1;

		void OnRefDestroyed(GameObject* who);
	};

}}