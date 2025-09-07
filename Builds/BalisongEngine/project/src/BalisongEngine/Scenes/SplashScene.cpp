#include "SplashScene.h"
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

#include "SineTransformComponent.h"
#include "SpriteRendererComponent.h"

#include "Input.h"
using namespace BalisongEngineFramework;

#include <glm/glm.hpp>
using namespace glm;

#include <iostream>
using namespace std;

// ===============================================================================

void SplashScene::OnInitialize()
{
	time = 0;
	Renderer::SetClearColor(.1f, .1f, .1f, 1); // bg color
	Camera::SetPosition(0, 0, 0);

	// ===============================================================================

	auto logo = new GameObject("[GO] Balisong Logo");
	logo->GetTransform()->SetLocalPosition(0, .15f);

	auto logo_sine = logo->AddComponent<SineTransformComponent>();
	logo_sine->sineRot = true;
	logo_sine->rotFreq = 3;
	logo_sine->rotAmp = 5;

	auto logo_sprite = logo->AddComponent<SpriteRendererComponent>();
	logo_sprite->SetTexture("../assets/splash/balisong_logo.png");
	logo_sprite->SetPixelsPerUnit(300);

	// ===============================================================================

	auto name_id_parent = new GameObject("[GO] Name ID Parent");
	auto name_id_parent_tr = name_id_parent->GetTransform();
	name_id_parent_tr->SetLocalPosition(0, -.5f);

	auto name_id = new GameObject("[GO] Name ID");
	name_id->GetTransform()->SetParent(name_id_parent_tr);

	auto name_id_sine = name_id->AddComponent<SineTransformComponent>();
	name_id_sine->sinePos = true;
	name_id_sine->posFreq = { 0,5 };
	name_id_sine->posAmp = { 0,.025f };

	auto name_id_sprite = name_id->AddComponent<SpriteRendererComponent>();
	name_id_sprite->SetTexture("../assets/splash/name_id.png");
	name_id_sprite->SetPixelsPerUnit(375);
}

void SplashScene::OnUpdate(float dt)
{
	time += dt;

	if (time >= 3 || Input::GetKeyDown(KeyCode::SPACE))
	{
		SceneStateMachine::LoadScene("MainMenuScene");
	}

	// testing camera
	//float y = sin(TimeEngine::getTime());
	//Camera::setPosition(0, y, 0);

	/*if (logo)
	{
		float logo_y_anim = sin(TimeEngine::getTime() * 5);
		logo->GetTransform()->SetPosition(0, .15f + logo_y_anim * .025f);
	}*/
}

// ===============================================================================

//void SplashScene::OnDeactivate()
//{
//	logo = nullptr;
//}