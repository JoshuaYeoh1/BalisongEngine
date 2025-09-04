#include "ShowcaseScene.h"
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

#include "MoveComponent.h"
#include "PlayerMoveComponent.h"
#include "SineTransformComponent.h"
#include "SpriteRendererComponent.h"
#include "SimpleShootComponent.h"
#include "TimerComponent.h"

#include "Input.h"
using namespace BalisongEngineFramework;

#include <glm/glm.hpp>
using namespace glm;

#include <iostream>
using namespace std;

// ===============================================================================

void ShowcaseScene::OnInitialize()
{
	time = 0;
	Renderer::SetClearColor(.5f, 1, 1, 1); // bg color
	Camera::SetPosition(0, 0, 0);

	// ===============================================================================

	auto info = new GameObject("[GO] Info");
	info->GetTransform()->SetLocalPosition({0,-.85f});

	auto info_sprite = info->AddComponent<SpriteRendererComponent>();
	info_sprite->SetTexture("../assets/showcase/info.png");
	info_sprite->SetPixelsPerUnit(300);
	info_sprite->SetZIndex(-1);

	// ===============================================================================

	auto potato_parent = new GameObject("[GO] Potato Parent");
	auto potato_parent_tr = potato_parent->GetTransform();

	auto potato_move = potato_parent->AddComponent<MoveComponent>();

	auto potato_player_move = potato_parent->AddComponent<PlayerMoveComponent>();
	potato_player_move->Init(potato_move, 1, { 0,1 });

	// ===============================================================================

	auto potato = new GameObject("[GO] Potato!");
	potato->GetTransform()->SetParent(potato_parent_tr);

	auto potato_sine = potato->AddComponent<SineTransformComponent>();
	potato_sine->sineRot = true;
	potato_sine->rotFreq = 2;
	potato_sine->rotAmp = 10;

	auto potato_sprite = potato->AddComponent<SpriteRendererComponent>();
	potato_sprite->SetTexture("../assets/showcase/potato.png");
	potato_sprite->SetPixelsPerUnit(450);

	// ===============================================================================

	auto potato_firepoint = new GameObject("[GO] Potato Firepoint");
	potato_firepoint->GetTransform()->SetParent(potato_parent_tr);

	auto potato_shoot = potato_firepoint->AddComponent<SimpleShootComponent>();
	potato_shoot->shootKeycode = KeyCode::SPACE;
	potato_shoot->shootCooldown = .3f;

	auto potato_shoot_timer = potato_firepoint->AddComponent<TimerComponent>();
	potato_shoot->cooldownTimerComponent = potato_shoot_timer;

	potato_shoot->projectileScale = .1f;
	potato_shoot->projectileSpeed = 4;
	potato_shoot->moveComponent = potato_move;
	potato_shoot->projectileTexturePath = "../assets/showcase/meatball.png";
	potato_shoot->projectileLifetime = .5f;
}

void ShowcaseScene::OnUpdate(float dt)
{
	time += dt;
}