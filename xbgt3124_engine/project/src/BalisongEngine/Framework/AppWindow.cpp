#include "AppWindow.h"
using namespace BalisongEngine;
using namespace BalisongEngineFramework;

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
using namespace std;

// ====================================================================

AppWindow::~AppWindow()
{
	GLFWwindow* window = static_cast<GLFWwindow*>(nativeWindow);
	glfwDestroyWindow(window);
	glfwTerminate();
}

// ====================================================================

void* AppWindow::GetNativeWindow()
{
	return nativeWindow;
}

// ====================================================================

// return 0 if fail, 1 if success
int AppWindow::Init(AppWindowData data)
{
	// try init GLFW
	if (!glfwInit())
	{
		cout << "Failed to initialize GLFW\n";
		return 0;
	}

	// cache the window data
	windowData = data;

	// set window context to OpenGL 2.1
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	// try create the window
	GLFWwindow* window = glfwCreateWindow(
		windowData.width, windowData.height,
		windowData.title.c_str(), nullptr, nullptr);

	if (window == nullptr)
	{
		cout << "Failed to create Window" << endl;
		return 0;
	}

	// set the window context as the current context
	// gl operations uses this window context
	glfwMakeContextCurrent(window);

	// try initialize glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return 0;
	}

	glfwSetWindowUserPointer(window, &windowData);

	glfwSetWindowCloseCallback(window, [](GLFWwindow* win)
	{
		AppWindowData* win_data = static_cast<AppWindowData*>(glfwGetWindowUserPointer(win));
		win_data->func_cb(AppWindowEventType::CLOSE, 0);
	});

	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* win, int width, int height)
	{
		AppWindowData* win_data = static_cast<AppWindowData*>(glfwGetWindowUserPointer(win));

		ResizeEventData event_data{ width, height };

		win_data->func_cb(AppWindowEventType::RESIZE, &event_data);

		glViewport(0, 0, width, height);
	});

	// window created successfully, cache the reference
	// and then return success
	nativeWindow = window;
	return 1;
}

// ====================================================================

void AppWindow::Update()
{
	GLFWwindow* window = static_cast<GLFWwindow*>(nativeWindow);
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void AppWindow::SetWindowEventCallback(const AppWindowEventCallbackFn& fn)
{
	windowData.func_cb = fn;
}

// ====================================================================

void AppWindow::SetWindowWidth(int width)
{
	windowData.width = width;

	if (nativeWindow)
	{
		glfwSetWindowSize(static_cast<GLFWwindow*>(nativeWindow), width, windowData.height);
	}
}
	
void AppWindow::SetWindowHeight(int height)
{
	windowData.height = height;

	if (nativeWindow)
	{
		glfwSetWindowSize(static_cast<GLFWwindow*>(nativeWindow), windowData.width, height);
	}
}

void AppWindow::SetWindowSize(int width, int height)
{
	windowData.width = width;
	windowData.height = height;

	if (nativeWindow)
	{
		glfwSetWindowSize(static_cast<GLFWwindow*>(nativeWindow), width, height);
	}
}