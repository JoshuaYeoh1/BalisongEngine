#pragma once
#include <functional>
#include <map>

namespace BalisongEngine{
namespace BalisongEngineFramework
{
	/// <summary>
	/// An event object may call multiple slots with the same signature. 
	/// You can connect functions to the event which will be called when the Invoke() method on the event object is invoked. 
	/// Any argument passed to Invoke() will be passed to the given functions.
	/// </summary>
	/// <typeparam name="...Args"></typeparam>
	template <typename... Args>
	class ActionEvent
	{
	public:

		/// <summary>
		/// ctor
		/// </summary>
		ActionEvent() = default;
		~ActionEvent() = default;

		// ===============================================================================
		
		/// <summary>
		/// Copy constructor and assignment create a new event.
		/// </summary>
		/// <param name=""></param>
		ActionEvent(ActionEvent const& /*unused*/) {}

		/// <summary>
		/// Copy assignment operator. Clears all current subscribers and performs a deep copy of the other ActionEvent
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		ActionEvent& operator=(ActionEvent const& other)
		{
			if (this != &other)
			{
				UnsubscribeAll();
			}
			return *this;
		}

		/// <summary>
		/// Move constructor and assignment operator work as expected.
		/// </summary>
		/// <param name="other"></param>
		ActionEvent(ActionEvent&& other) noexcept :
			subscribers(std::move(other.subscribers)), current_id(other.current_id) {}

		/// <summary>
		/// Move assignment operator. Transfers ownership of the subscribers and ID from the other ActionEvent
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		ActionEvent& operator=(ActionEvent&& other) noexcept
		{
			if (this != &other) {
				subscribers = std::move(other.subscribers);
				current_id = other.current_id;
			}
			return *this;
		}

		// ===============================================================================

		/// <summary>
		/// Connects a std::function to the event. The returned value can be used to disconnect the function again.
		/// </summary>
		/// <param name="slot"></param>
		/// <returns></returns>
		int Subscribe(std::function<void(Args...)> const& slot) const
		{
			subscribers.insert(std::make_pair(++current_id, slot));
			return current_id;
		}

		/// <summary>
		/// Convenience method to connect a member function of an object to this event.
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="reference"></param>
		/// <param name="function"></param>
		/// <returns></returns>
		template <typename T>
		int Subscribe(T* reference, void (T::* function)(Args...))
		{
			return Subscribe([=](Args... args)
			{
				(reference->*function)(args...);
			});
		}

		/// <summary>
		/// Convenience method to connect a const member function of an object to this event.
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="reference"></param>
		/// <param name="function"></param>
		/// <returns></returns>
		template <typename T>
		int Subscribe(T* reference, void (T::* function)(Args...) const)
		{
			return Subscribe([=](Args... args)
			{
				(reference->*function)(args...);
			});
		}

		// ===============================================================================

		/// <summary>
		/// Disconnects a previously connected function.
		/// </summary>
		/// <param name="id"></param>
		void Unsubscribe(int id) const
		{
			subscribers.erase(id);
		}

		/// <summary>
		/// Disconnects all previously connected functions.
		/// </summary>
		void UnsubscribeAll() const
		{
			subscribers.clear();
		}

		// ===============================================================================

		/// <summary>
		/// Calls all connected functions.
		/// </summary>
		/// <param name="...p"></param>
		void Invoke(Args... p)
		{
			for (auto const& it : subscribers)
			{
				if (it.second) // nullptr check
					it.second(p...);
			}
		}

		/// <summary>
		/// Calls all connected functions except for one.
		/// </summary>
		/// <param name="excludedConnectionID"></param>
		/// <param name="...p"></param>
		void InvokeAllExcept(int excludedConnectionID, Args... p)
		{
			for (auto const& it : subscribers)
			{
				if (it.first != excludedConnectionID)
				{
					if (it.second) // nullptr check
						it.second(p...);
				}
			}
		}

		/// <summary>
		/// Calls only one connected function.
		/// </summary>
		/// <param name="connectionID"></param>
		/// <param name="...p"></param>
		void InvokeFor(int connectionID, Args... p)
		{
			auto const& it = subscribers.find(connectionID);

			if (it != subscribers.end())
			{
				it->second(p...);
			}
		}

		// ===============================================================================

	private:

		mutable std::map<int, std::function<void(Args...)>> subscribers;
		mutable int current_id{ 0 };
	};

}
}