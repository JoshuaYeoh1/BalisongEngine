#include "Input.h"
using namespace BalisongEngine;

#include "AppWindow.h"
using namespace BalisongEngineFramework;

#include <glfw/glfw3.h>

#include <string>
#include <iostream>
using namespace std;

// ====================================================================

static GLFWwindow* window_Impl; // [4]

// define the unordered_maps
unordered_map<KeyCode, bool> Input::key_states_current;
unordered_map<KeyCode, bool> Input::key_states_previous;

unordered_map<MouseCode, bool> Input::mouse_states_current;
unordered_map<MouseCode, bool> Input::mouse_states_previous;
	
// ====================================================================

void Input::Init(void* proc_address)
{
	AppWindow* appWindow = static_cast<AppWindow*>(proc_address);
	void* nativeWindow = appWindow->GetNativeWindow();
	window_Impl = static_cast<GLFWwindow*>(nativeWindow);
		
	// set sticky
	glfwSetInputMode(window_Impl, GLFW_STICKY_KEYS, GLFW_TRUE);
	glfwSetInputMode(window_Impl, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
		
	// init defaults
	// key states
	key_states_current = {
		{KeyCode::UNKNOWN, false},
		{KeyCode::SPACE, false},
		{KeyCode::APOSTROPHE, false},
		{KeyCode::COMMA, false},
		{KeyCode::MINUS, false},
		{KeyCode::PERIOD, false},
		{KeyCode::SLASH, false},
		{KeyCode::ALPHA_0, false},
		{KeyCode::ALPHA_1, false},
		{KeyCode::ALPHA_2, false},
		{KeyCode::ALPHA_3, false},
		{KeyCode::ALPHA_4, false},
		{KeyCode::ALPHA_5, false},
		{KeyCode::ALPHA_6, false},
		{KeyCode::ALPHA_7, false},
		{KeyCode::ALPHA_8, false},
		{KeyCode::ALPHA_9, false},
		{KeyCode::SEMICOLON, false},
		{KeyCode::EQUAL, false},
		{KeyCode::A, false},
		{KeyCode::B, false},
		{KeyCode::C, false},
		{KeyCode::D, false},
		{KeyCode::E, false},
		{KeyCode::F, false},
		{KeyCode::G, false},
		{KeyCode::H, false},
		{KeyCode::I, false},
		{KeyCode::J, false},
		{KeyCode::K, false},
		{KeyCode::L, false},
		{KeyCode::M, false},
		{KeyCode::N, false},
		{KeyCode::O, false},
		{KeyCode::P, false},
		{KeyCode::Q, false},
		{KeyCode::R, false},
		{KeyCode::S, false},
		{KeyCode::T, false},
		{KeyCode::U, false},
		{KeyCode::V, false},
		{KeyCode::W, false},
		{KeyCode::X, false},
		{KeyCode::Y, false},
		{KeyCode::Z, false},
		{KeyCode::LEFT_BRACKET, false},
		{KeyCode::BACKSLASH, false},
		{KeyCode::RIGHT_BRACKET, false},
		{KeyCode::GRAVE_ACCENT, false},
		{KeyCode::WORLD_1, false},
		{KeyCode::WORLD_2, false},
		{KeyCode::ESCAPE, false},
		{KeyCode::ENTER, false},
		{KeyCode::TAB, false},
		{KeyCode::BACKSPACE, false},
		{KeyCode::INSERT, false},
		{KeyCode::DELETE, false},
		{KeyCode::RIGHT, false},
		{KeyCode::LEFT, false},
		{KeyCode::DOWN, false},
		{KeyCode::UP, false},
		{KeyCode::PAGE_UP, false},
		{KeyCode::PAGE_DOWN, false},
		{KeyCode::HOME, false},
		{KeyCode::END, false},
		{KeyCode::CAPS_LOCK, false},
		{KeyCode::SCROLL_LOCK, false},
		{KeyCode::NUM_LOCK, false},
		{KeyCode::PRINT_SCREEN, false},
		{KeyCode::PAUSE, false},
		{KeyCode::F1, false},
		{KeyCode::F2, false},
		{KeyCode::F3, false},
		{KeyCode::F4, false},
		{KeyCode::F5, false},
		{KeyCode::F6, false},
		{KeyCode::F7, false},
		{KeyCode::F8, false},
		{KeyCode::F9, false},
		{KeyCode::F10, false},
		{KeyCode::F11, false},
		{KeyCode::F12, false},
		{KeyCode::F13, false},
		{KeyCode::F14, false},
		{KeyCode::F15, false},
		{KeyCode::F16, false},
		{KeyCode::F17, false},
		{KeyCode::F18, false},
		{KeyCode::F19, false},
		{KeyCode::F20, false},
		{KeyCode::F21, false},
		{KeyCode::F22, false},
		{KeyCode::F23, false},
		{KeyCode::F24, false},
		{KeyCode::F25, false},
		{KeyCode::KP_0, false},
		{KeyCode::KP_1, false},
		{KeyCode::KP_2, false},
		{KeyCode::KP_3, false},
		{KeyCode::KP_4, false},
		{KeyCode::KP_5, false},
		{KeyCode::KP_6, false},
		{KeyCode::KP_7, false},
		{KeyCode::KP_8, false},
		{KeyCode::KP_9, false},
		{KeyCode::KP_DECIMAL, false},
		{KeyCode::KP_DIVIDE, false},
		{KeyCode::KP_MULTIPLY, false},
		{KeyCode::KP_SUBTRACT, false},
		{KeyCode::KP_ADD, false},
		{KeyCode::KP_ENTER, false},
		{KeyCode::KP_EQUAL, false},
		{KeyCode::LEFT_SHIFT, false},
		{KeyCode::LEFT_CONTROL, false},
		{KeyCode::LEFT_ALT, false},
		{KeyCode::LEFT_SUPER, false},
		{KeyCode::RIGHT_SHIFT, false},
		{KeyCode::RIGHT_CONTROL, false},
		{KeyCode::RIGHT_ALT, false},
		{KeyCode::RIGHT_SUPER, false},
		{KeyCode::MENU, false},
	};
		
	// In C++, doing this makes a copy of the unordered_map.
	// This works in our favour, reducing boilerplate codes.
	key_states_previous = key_states_current;

	// mouse states
	mouse_states_current = {
		{MouseCode::UNKNOWN, false},
		{MouseCode::LEFT, false},
		{MouseCode::RIGHT, false},
		{MouseCode::MIDDLE, false},
	};

	mouse_states_previous = mouse_states_current;
}

void Input::Process()
{
	// KEYS ====================================================================

	// The iterator
	unordered_map<KeyCode, bool>::iterator it;
	// it->first for key
	// it->second for value

	// ITERATE key_states_previous, FOR EVERY element
	for (it = key_states_previous.begin(); it != key_states_previous.end(); it++)
	{
		// element.VALUE = key_states_current[element.KEY]
		it->second = key_states_current[it->first];
	}
			
	// ITERATE key_states_current, FOR EVERY element
	for (it = key_states_current.begin(); it != key_states_current.end(); it++)
	{
		// element.VALUE = glfwGetKey(window_Impl, (int)element.KEY)
		it->second = glfwGetKey(window_Impl, (int)it->first);
	}

	// MOUSE ====================================================================

	unordered_map<MouseCode, bool>::iterator it_mb;

	for (it_mb = mouse_states_previous.begin(); it_mb != mouse_states_previous.end(); it_mb++)
	{
		it_mb->second = mouse_states_current[it_mb->first];
	}

	for (it_mb = mouse_states_current.begin(); it_mb != mouse_states_current.end(); it_mb++)
	{
		it_mb->second = glfwGetMouseButton(window_Impl, (int)it_mb->first);
	}
}

// KEYS ==============================================================

bool Input::GetKey(const KeyCode key_code)
{
	// FIND keycode IN key_states_current
	unordered_map<KeyCode, bool>::iterator it = key_states_current.find(key_code);

	// IF FOUND what you're looking for, it won't reach the end
	if (it != key_states_current.end())
	{
		// RETURN key.VALUE
		return it->second;
	}
	else return false;
}

bool Input::GetKeyDown(const KeyCode key_code)
{
	bool current_value = false;
	bool previous_value = false;

	// FIND keycode IN key_states_current
	unordered_map<KeyCode, bool>::iterator it = key_states_current.find(key_code);

	// IF FOUND key
	if (it != key_states_current.end())
	{
		// curValue = key.VALUE
		current_value = it->second;

		// oldValue = key_states_previous[keyCode]
		previous_value = key_states_previous[key_code];
	}

	// RETURN curValue IS TRUE AND oldValue IS FALSE
	return current_value && !previous_value;
}

bool Input::GetKeyUp(const KeyCode key_code)
{
	bool current_value = false;
	bool previous_value = false;

	unordered_map<KeyCode, bool>::iterator it = key_states_current.find(key_code);

	if (it != key_states_current.end())
	{
		current_value = it->second;

		previous_value = key_states_previous[key_code];
	}

	// RETURN curValue IS FALSE AND oldValue IS TRUE
	return !current_value && previous_value;
}


// ==============================================================

bool Input::GetAnyKey()
{
	unordered_map<KeyCode, bool>::iterator it;

	for (it = key_states_current.begin(); it != key_states_current.end(); it++)
	{
		if (it->second)
		{
			return true;
		}
		else continue;
	}

	return false;
}

bool Input::GetAnyKeyDown()
{
	bool current_value = false;
	bool previous_value = false;

	unordered_map<KeyCode, bool>::iterator it;

	for (it = key_states_current.begin(); it != key_states_current.end(); it++)
	{
		if (it->second)
		{
			current_value = it->second;

			previous_value = key_states_previous[it->first];
		}
		else continue;
	}

	return current_value && !previous_value;
}

// ==============================================================

float Input::GetAxis(const string axis)
{
	float input = 0;

	if (axis == "Horizontal")
	{
		if (Input::GetKey(KeyCode::D) || Input::GetKey(KeyCode::RIGHT))
		{
			input = 1;
		}
		else if (Input::GetKey(KeyCode::A) || Input::GetKey(KeyCode::LEFT))
		{
			input = -1;
		}
	}
	else if (axis == "Vertical")
	{
		if (Input::GetKey(KeyCode::W) || Input::GetKey(KeyCode::UP))
		{
			input = 1;
		}
		else if (Input::GetKey(KeyCode::S) || Input::GetKey(KeyCode::DOWN))
		{
			input = -1;
		}
	}

	return input;
}

// MOUSE ==============================================================

bool Input::GetMouse(const MouseCode mouse_code)
{
	unordered_map<MouseCode, bool>::iterator it = mouse_states_current.find(mouse_code);

	if (it != mouse_states_current.end())
	{
		return it->second;
	}
	else return false;
}

bool Input::GetMouseDown(const MouseCode mouse_code)
{
	bool current_value = false;
	bool previous_value = false;

	unordered_map<MouseCode, bool>::iterator it = mouse_states_current.find(mouse_code);

	if (it != mouse_states_current.end())
	{
		current_value = it->second;

		previous_value = mouse_states_previous[mouse_code];
	}

	return current_value && !previous_value;
}

bool Input::GetMouseUp(const MouseCode mouse_code)
{
	bool current_value = false;
	bool previous_value = false;

	unordered_map<MouseCode, bool>::iterator it = mouse_states_current.find(mouse_code);

	if (it != mouse_states_current.end())
	{
		current_value = it->second;

		previous_value = mouse_states_previous[mouse_code];
	}

	return !current_value && previous_value;
}

// ==============================================================

glm::vec2 Input::GetMousePosition()
{
	double x, y;

	// GET CURSOR POSITION FROM GLFW using window_Impl AND PASSING REFERENCE OF x AND y
	glfwGetCursorPos(window_Impl, &x, &y);

	// convert cursor origin from top left to bottom left
	// Convert the y-coordinate (inverted origin)
	int windowHeight;
	glfwGetWindowSize(window_Impl, nullptr, &windowHeight);

	glm::vec2 mouse_pos = glm::vec2(x, windowHeight - y);

	//cout << "Mouse Cursor at: " << mouse_pos.x << ", " << mouse_pos.y << endl;

	return mouse_pos;
}