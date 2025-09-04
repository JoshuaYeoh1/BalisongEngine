#include "InputTestScene.h"
#include "GameObject.h"
#include "PrefabManager.h"
#include "TransformComponent.h"
#include "Renderer.h"
#include "Camera.h"
#include "SceneStateMachine.h"
using namespace BalisongEngine;
using namespace BalisongEngineOCM;
using namespace BalisongEngineComponents;
using namespace BalisongEngineRenderer;
using namespace BalisongEngineScenes;

#include "Input.h"
using namespace BalisongEngineFramework;

#include <glm/glm.hpp>
using namespace glm;

#include <iostream>
using namespace std;

// ===============================================================================

void InputTestScene::OnInitialize()
{
	Renderer::SetClearColor(0, 0, .25f, 1);

	time = 0;
}

void InputTestScene::OnUpdate(float deltaTime)
{
	time += deltaTime;

	//if (time > 2.0f)

	// mouse test
	if (Input::GetMouseDown(MouseCode::LEFT))
	{
		cout << "Pressed Left Mouse" << endl;
	}
	if (Input::GetMouse(MouseCode::LEFT))
	{
		cout << "Pressing Left Mouse" << endl;
	}
	if (Input::GetMouseUp(MouseCode::LEFT))
	{
		cout << "Released Left Mouse" << endl;
	}
	if (Input::GetMouseDown(MouseCode::MIDDLE))
	{
		cout << "Pressed Middle Mouse" << endl;
	}
	if (Input::GetMouse(MouseCode::MIDDLE))
	{
		cout << "Pressing Middle Mouse" << endl;
	}
	if (Input::GetMouseUp(MouseCode::MIDDLE))
	{
		cout << "Released Middle Mouse" << endl;
	}
	if (Input::GetMouseDown(MouseCode::RIGHT))
	{
		cout << "Pressed Right Mouse" << endl;

		glm::vec2 pos = Input::GetMousePosition();
	}
	if (Input::GetMouse(MouseCode::RIGHT))
	{
		cout << "Pressing Right Mouse" << endl;
	}
	if (Input::GetMouseUp(MouseCode::RIGHT))
	{
		cout << "Released Right Mouse" << endl;

		glm::vec2 pos = Input::GetMousePosition();
	}

	// get axis test
	float input_y = Input::GetAxis("Vertical");

	if (input_y != 0)
		cout << "GetAxis Vertical: " << input_y << endl;

	// any key test
	//if (Input::GetAnyKeyDown())
	//{
	//	cout << "AnyKey just pressed" << endl;
	//}
	//if (Input::GetAnyKey())
	//{
	//	cout << "AnyKey is pressing" << endl;
	//}
}

void InputTestScene::OnRender()
{
	
}
