#include "AppWindow.h"

// ===============================================================================

namespace BalisongEngine{
namespace BalisongEngineFramework
{
	/// <summary>
	/// The application of the Game Engine
	/// </summary>
	class Application
	{
	private:

		static Application* instance;
		
		AppWindow window;

		bool isRunning = false;

		// frame limiting
		unsigned int targetFrameRate = 0;
		float frameTime = 0;

		// ====================================================================

		void OnReceiveAppWindowEvent(AppWindowEventType& event_type, void* payload);

		void AppHotkeys();

		// ====================================================================

	public:

		/// <summary>
		/// Creates an AppWindow
		/// </summary>
		/// <param name="width">Width of AppWindow</param>
		/// <param name="height">Height of AppWindow</param>
		/// <param name="title">Title of AppWindow</param>
		/// <returns>1 if success, 0 if fail</returns>
		int Init(int width, int height, std::string title);
		
		// ====================================================================

		// <summary>
		/// Gets the window width
		/// </summary>
		/// <returns>int pixels</returns>
		int GetWindowWidth() const { return window.GetWindowWidth(); }
		/// <summary>
		/// Gets the window height
		/// </summary>
		/// <returns>int pixels</returns>
		int GetWindowHeight() const { return window.GetWindowHeight(); }

		/// <summary>
		/// Sets the window width
		/// </summary>
		/// <param name="width">int pixels</param>
		void SetWindowWidth(int width) { window.SetWindowWidth(width); }
		/// <summary>
		/// Sets the window height
		/// </summary>
		/// <param name="height">int pixels</param>
		void SetWindowHeight(int height) { window.SetWindowHeight(height); }
		/// <summary>
		/// Sets the window size
		/// </summary>
		/// <param name="width">int pixels</param>
		/// <param name="height">int pixels</param>
		void SetWindowSize(int width, int height) { window.SetWindowSize(width, height); }

		// ====================================================================

		/// <summary>
		/// Runs the Application
		/// </summary>
		void Run();

		/// <summary>
		/// Cleans up the Application
		/// </summary>
		void CleanUp();

		/// <summary>
		/// Sets the frame limit (Max FPS)
		/// </summary>
		/// <param name="frame_rate">int fps</param>
		static void SetTargetFrameRate(unsigned int frame_rate);

		/// <summary>
		/// Quits the Application
		/// </summary>
		static void Quit();
	};
}}
