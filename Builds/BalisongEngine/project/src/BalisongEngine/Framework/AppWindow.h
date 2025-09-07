#pragma once
#include <string>
#include <functional>

// ===============================================================================

namespace BalisongEngine{
namespace BalisongEngineFramework
{
	/// <summary>
	/// Types of events that can occur in an AppWindow
	/// </summary>
	enum class AppWindowEventType
	{
		CLOSE,
		RESIZE,
	};

	/// <summary>
	/// Data for a window resize event, containing the new width and height
	/// </summary>
	struct ResizeEventData
	{
		/// <summary>
		/// New window width
		/// </summary>
		int width;
		/// <summary>
		/// New window height
		/// </summary>
		int height;
	};

	// ====================================================================

	/// <summary>
	/// Callback function type for handling AppWindow events
	/// </summary>
	using AppWindowEventCallbackFn = std::function<void(AppWindowEventType, void*)>; // type aliasing

	// ====================================================================

	/// <summary>
	/// Contains properties of the application window
	/// </summary>
	struct AppWindowData
	{
		/// <summary>
		/// The width of the window
		/// </summary>
		int width = 600;
		/// <summary>
		/// The height of the window
		/// </summary>
		int height = 600;

		/// <summary>
		/// The title of the window
		/// </summary>
		std::string title = "Balisong Engine";

		/// <summary>
		/// Ctor that initializes the window data with default values
		/// </summary>
		AppWindowData() {}

		/// <summary>
		/// Ctor that initializes the window with the window size and title
		/// </summary>
		/// <param name="width"></param>
		/// <param name="height"></param>
		/// <param name="title"></param>
		AppWindowData(int width, int height, std::string title)
			: width(width), height(height), title(title) {}

		/// <summary>
		/// Callback function for handling window events
		/// </summary>
		AppWindowEventCallbackFn func_cb;
	};

	// ====================================================================

	/// <summary>
	/// The application window, managing its properties and events
	/// </summary>
	class AppWindow
	{
	private:

		/// <summary>
		/// Data related to the application window
		/// </summary>
		AppWindowData windowData;
		/// <summary>
		/// Pointer to the platform-specific window implementation
		/// </summary>
		void* nativeWindow = nullptr;

		// ====================================================================

	public:

		~AppWindow();

		// ====================================================================

		/// <summary>
		/// Gets the native window
		/// </summary>
		/// <returns>void* nativeWindow</returns>
		void* GetNativeWindow();

		/// <summary>
		/// Initializes a GLFW-based window with OpenGL context, sets up user-defined callbacks for window events like close and resize
		/// </summary>
		/// <param name="data"></param>
		/// <returns>int Success (1) or Failure (0)</returns>
		int Init(AppWindowData data);

		/// <summary>
		/// Updates the window by swapping the front and back buffers for rendering and processing any pending window events
		/// </summary>
		void Update();

		// ====================================================================

		/// <summary>
		/// Sets user-defined callback function to handle window events by storing it in the AppWindowData
		/// </summary>
		/// <param name="fn">AppWindow Event Callback Fn</param>
		void SetWindowEventCallback(const AppWindowEventCallbackFn& fn);

		// ====================================================================

		/// <summary>
		/// Gets the window width
		/// </summary>
		/// <returns>int pixels</returns>
		int GetWindowWidth() const { return windowData.width; }
		/// <summary>
		/// Gets the window height
		/// </summary>
		/// <returns>int pixels</returns>
		int GetWindowHeight() const { return windowData.height; }

		/// <summary>
		/// Sets the window width
		/// </summary>
		/// <param name="width">int pixels</param>
		void SetWindowWidth(int width);
		/// <summary>
		/// Sets the window height
		/// </summary>
		/// <param name="height">int pixels</param>
		void SetWindowHeight(int height);
		/// <summary>
		/// Sets the window size
		/// </summary>
		/// <param name="width">int pixels</param>
		/// <param name="height">int pixels</param>
		void SetWindowSize(int width, int height);
	};

}}
