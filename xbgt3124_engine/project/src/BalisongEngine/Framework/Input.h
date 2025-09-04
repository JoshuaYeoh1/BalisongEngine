#pragma once
#include <unordered_map>
#include <glm/vec2.hpp>
#include <string>

// ===============================================================================

namespace BalisongEngine{
namespace BalisongEngineFramework
{
	/// <summary>
	/// List of keyboard buttons
	/// </summary>
	enum class KeyCode
	{
        UNKNOWN = -1,
		SPACE = 32,
        APOSTROPHE = 39,
        COMMA = 44,
        MINUS = 45,
        PERIOD = 46,
        SLASH = 47,
        ALPHA_0 = 48,
        ALPHA_1 = 49,
        ALPHA_2 = 50,
        ALPHA_3 = 51,
        ALPHA_4 = 52,
        ALPHA_5 = 53,
        ALPHA_6 = 54,
        ALPHA_7 = 55,
        ALPHA_8 = 56,
        ALPHA_9 = 57,
        SEMICOLON = 59,
        EQUAL = 61,
        A = 65,
        B = 66,
        C = 67,
        D = 68,
        E = 69,
        F = 70,
        G = 71,
        H = 72,
        I = 73,
        J = 74,
        K = 75,
        L = 76,
        M = 77,
        N = 78,
        O = 79,
        P = 80,
        Q = 81,
        R = 82,
        S = 83,
        T = 84,
        U = 85,
        V = 86,
        W = 87,
        X = 88,
        Y = 89,
        Z = 90,
        LEFT_BRACKET = 91,
        BACKSLASH = 92,
        RIGHT_BRACKET = 93,
        GRAVE_ACCENT = 96,
        WORLD_1 = 161,
        WORLD_2 = 162,
        ESCAPE = 256,
        ENTER = 257,
        TAB = 258,
        BACKSPACE = 259,
        INSERT = 260,
        DELETE = 261,
        RIGHT = 262,
        LEFT = 263,
        DOWN = 264,
        UP = 265,
        PAGE_UP = 266,
        PAGE_DOWN = 267,
        HOME = 268,
        END = 269,
        CAPS_LOCK = 280,
        SCROLL_LOCK = 281,
        NUM_LOCK = 282,
        PRINT_SCREEN = 283,
        PAUSE = 284,
        F1 = 290,
        F2 = 291,
        F3 = 292,
        F4 = 293,
        F5 = 294,
        F6 = 295,
        F7 = 296,
        F8 = 297,
        F9 = 298,
        F10 = 299,
        F11 = 300,
        F12 = 301,
        F13 = 302,
        F14 = 303,
        F15 = 304,
        F16 = 305,
        F17 = 306,
        F18 = 307,
        F19 = 308,
        F20 = 309,
        F21 = 310,
        F22 = 311,
        F23 = 312,
        F24 = 313,
        F25 = 314,
        KP_0 = 320,
        KP_1 = 321,
        KP_2 = 322,
        KP_3 = 323,
        KP_4 = 324,
        KP_5 = 325,
        KP_6 = 326,
        KP_7 = 327,
        KP_8 = 328,
        KP_9 = 329,
        KP_DECIMAL = 330,
        KP_DIVIDE = 331,
        KP_MULTIPLY = 332,
        KP_SUBTRACT = 333,
        KP_ADD = 334,
        KP_ENTER = 335,
        KP_EQUAL = 336,
        LEFT_SHIFT = 340,
        LEFT_CONTROL = 341,
        LEFT_ALT = 342,
        LEFT_SUPER = 343,
        RIGHT_SHIFT = 344,
        RIGHT_CONTROL = 345,
        RIGHT_ALT = 346,
        RIGHT_SUPER = 347,
        MENU = 348,
    };
    
    /// <summary>
    /// List of mouse buttons
    /// </summary>
    enum class MouseCode
    {
        UNKNOWN = -1,
        LEFT = 0,
        RIGHT = 1,
        MIDDLE = 2,
    };

    // ==============================================================

	/// <summary>
	/// The static class to detect user input for keyboard and mouse
	/// </summary>
	class Input
	{
	private:

		friend class Application;

		Input() = delete;

		static void Init(void* procAddress);
		static void Process();

        // ==============================================================

		// declare static unordered_maps
		static std::unordered_map<KeyCode, bool> key_states_current;
		static std::unordered_map<KeyCode, bool> key_states_previous;
        
        static std::unordered_map<MouseCode, bool> mouse_states_current;
		static std::unordered_map<MouseCode, bool> mouse_states_previous;

        // ==============================================================

	public:

        /// <summary>
        /// Checks if key is being held down
        /// </summary>
        /// <param name="key_code">enum KeyCode</param>
        /// <returns>bool</returns>
        static bool GetKey(const KeyCode key_code);
        /// <summary>
        /// Checks if key was just pressed
        /// </summary>
        /// <param name="key_code">enum KeyCode</param>
        /// <returns>bool</returns>
        static bool GetKeyDown(const KeyCode key_code);
        /// <summary>
        /// Checks if key was just released
        /// </summary>
        /// <param name="key_code">enum KeyCode</param>
        /// <returns>bool</returns>
        static bool GetKeyUp(const KeyCode key_code);

        // ==============================================================

        /// <summary>
        /// Checks if any key is being held down
        /// </summary>
        /// <returns>bool</returns>
        static bool GetAnyKey();
        /// <summary>
        /// Checks if any key was just pressed
        /// </summary>
        /// <returns>bool</returns>
        static bool GetAnyKeyDown();

        // ==============================================================

        /// <summary>
        /// Gets the Horizontal or Vertical input direction using A and D or Left and Right arrow keys
        /// </summary>
        /// <param name="axis">Choose Horizontal or Vertical</param>
        /// <returns>float input direction from 0 to 1</returns>
        static float GetAxis(const std::string axis);

        // ==============================================================

        /// <summary>
        /// Checks if mouse is being held down
        /// </summary>
        /// <param name="mouse_code">enum MouseCode</param>
        /// <returns>bool</returns>
        static bool GetMouse(const MouseCode mouse_code);
        /// <summary>
        /// Checks if mouse was just pressed
        /// </summary>
        /// <param name="mouse_code">enum MouseCode</param>
        /// <returns>bool</returns>
        static bool GetMouseDown(const MouseCode mouse_code);
        /// <summary>
        /// Checks if mouse was just released
        /// </summary>
        /// <param name="mouse_code">enum MouseCode</param>
        /// <returns>bool</returns>
        static bool GetMouseUp(const MouseCode mouse_code);

        // ==============================================================

        /// <summary>
        /// Gets the mouse position in screen space
        /// </summary>
        /// <returns>vec2 mouse position</returns>
        static glm::vec2 GetMousePosition();
	};
}}