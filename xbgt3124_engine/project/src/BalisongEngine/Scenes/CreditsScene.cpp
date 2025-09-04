#include "CreditsScene.h"
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

#include <glm/glm.hpp>
using namespace glm;

#include <iostream>
using namespace std;

// ===============================================================================

void CreditsScene::OnInitialize()
{
	time = 0;
	Renderer::SetClearColor(0, 0, 0, 1); // bg color
	Camera::SetPosition(0, 0, 0);

	// ===============================================================================

	auto credits = PrefabManager::Instantiate("Credits");

	auto back = PrefabManager::Instantiate("CreditsBackButton");
}

// ===============================================================================

void CreditsScene::OnUpdate(float dt)
{
	time += dt;
}