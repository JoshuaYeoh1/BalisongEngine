#include "Prefabs.h"
#include "GameObject.h"
#include "PrefabManager.h"
#include "TransformComponent.h"
using namespace BalisongEngine;
using namespace BalisongEngineOCM;
using namespace BalisongEngineComponents;

#include "SpriteRendererComponent.h"
#include "ButtonComponent.h"
#include "SineTransformComponent.h"
#include "FollowMouseComponent.h"
#include "MoveComponent.h"
#include "PursuitComponent.h"
#include "AnimatorComponent.h"
#include "MoveAnimComponent.h"
#include "CameraBorderComponent.h"
#include "TimerComponent.h"
#include "ShootComponent.h"
#include "EnemySpawnerComponent.h"
#include "RandomTransformComponent.h"
#include "BoxColliderComponent.h"
#include "CircleColliderComponent.h"
#include "DestroyOnCollideComponent.h"
#include "DeflectComponent.h"
#include "SpawnOnCollideComponent.h"
#include "SpawnOnDestroyComponent.h"
#include "AudioSourceComponent.h"
#include "ScrollerComponent.h"
#include "FollowCameraComponent.h"

#include "Random.h"
#include "AudioManager.h"
using namespace BalisongEngineFramework;

#include "SceneStateMachine.h"
using namespace BalisongEngineScenes;

#include <glm/glm.hpp>
using namespace glm;

#include <iostream>
using namespace std;

// ===============================================================================

GameObject* TitlePrefab::CreateInstance()
{
	auto go = new GameObject("[GO] Title");
	go->GetTransform()->TranslateLocal(0, .25f);

	auto sprite = go->AddComponent<SpriteRendererComponent>();
	sprite->SetTexture("../assets/ui/title/title.png");
	sprite->SetPixelsPerUnit(400);

	auto sine = go->AddComponent<SineTransformComponent>();
	sine->sinePos = true;
	sine->posFreq = { 0,1.5f };
	sine->posAmp = { 0,.05f };
	sine->sineRot = true;
	sine->rotFreq = 2;
	sine->rotAmp = 3;

	return go;
}

// ===============================================================================

GameObject* PlayButtonPrefab::CreateInstance()
{
	auto go = new GameObject("[GO] Play Button");
	go->GetTransform()->TranslateLocal(0, -.15f);

	auto tr = go->GetTransform();
	auto pos = tr->GetWorldPosition();

	auto sprite = go->AddComponent<SpriteRendererComponent>();
	sprite->SetTexture("../assets/ui/button/play.png");
	sprite->SetPixelsPerUnit(150);

	auto button = go->AddComponent<ButtonComponent>();
	button->SetSprite(sprite);
	button->hoverTint = sprite->GetTint();
	button->hoverTexture = "../assets/ui/button/play_hover.png";

	button->HoverEnterEvent.Subscribe([pos]()
	{
		AudioManager::Play("ButtonHover", pos);
	});

	button->PressEvent.Subscribe([pos]()
	{
		AudioManager::Play("ButtonClick", pos);
	});

	button->ReleaseEvent.Subscribe([pos]()
	{
		SceneStateMachine::LoadNextScene();
	});

	auto sine = go->AddComponent<SineTransformComponent>();
	sine->sineRot = true;
	sine->rotFreq = 3;
	sine->rotAmp = 3;

	return go;
}

// ===============================================================================

GameObject* RetryButtonPrefab::CreateInstance()
{
	auto go = new GameObject("[GO] Retry Button");

	auto tr = go->GetTransform();
	auto pos = tr->GetWorldPosition();

	auto sprite = go->AddComponent<SpriteRendererComponent>();
	sprite->SetTexture("../assets/ui/button/retry.png");
	sprite->SetPixelsPerUnit(150);

	auto button = go->AddComponent<ButtonComponent>();
	button->SetSprite(sprite);
	button->hoverTint = sprite->GetTint();
	button->hoverTexture = "../assets/ui/button/retry_hover.png";
	
	button->HoverEnterEvent.Subscribe([pos]()
	{
		AudioManager::Play("ButtonHover", pos);
	});

	button->PressEvent.Subscribe([pos]()
	{
		AudioManager::Play("ButtonClick", pos);
	});

	button->ReleaseEvent.Subscribe([]()
	{
		SceneStateMachine::ReloadScene();
	});

	auto sine = go->AddComponent<SineTransformComponent>();
	sine->sineRot = true;
	sine->rotFreq = 3;
	sine->rotAmp = 3;

	return go;
}

// ===============================================================================

GameObject* MenuButtonPrefab::CreateInstance()
{
	auto go = new GameObject("[GO] Menu Button");

	auto tr = go->GetTransform();
	auto pos = tr->GetWorldPosition();

	auto sprite = go->AddComponent<SpriteRendererComponent>();
	sprite->SetTexture("../assets/ui/button/menu.png");
	sprite->SetPixelsPerUnit(150);

	auto button = go->AddComponent<ButtonComponent>();
	button->SetSprite(sprite);
	button->hoverTint = sprite->GetTint();
	button->hoverTexture = "../assets/ui/button/menu_hover.png";

	button->HoverEnterEvent.Subscribe([pos]()
	{
		AudioManager::Play("ButtonHover", pos);
	});

	button->PressEvent.Subscribe([pos]()
	{
		AudioManager::Play("ButtonClick", pos);
	});

	button->ReleaseEvent.Subscribe([]()
	{
		SceneStateMachine::LoadScene("MainMenuScene");
	});

	auto sine = go->AddComponent<SineTransformComponent>();
	sine->sineRot = true;
	sine->rotFreq = 3;
	sine->rotAmp = 3;

	return go;
}

// ===============================================================================

GameObject* TutorialPrefab::CreateInstance()
{
	auto go = new GameObject("[GO] Tutorial");
	go->GetTransform()->TranslateLocal(0, -.75f);

	auto sprite = go->AddComponent<SpriteRendererComponent>();
	sprite->SetTexture("../assets/level/tutorial.png");
	sprite->SetPixelsPerUnit(600);

	return go;
}

// ===============================================================================

GameObject* MousePrefab::CreateInstance()
{
	auto go = new GameObject("[GO] Mouse");

	go->AddComponent<FollowMouseComponent>();

	return go;
}

// ===============================================================================

GameObject* PlayerPrefab::CreateInstance()
{
	auto go = new GameObject("[GO] Player");
	go->tag = "Player";

	auto tr = go->GetTransform();
	auto pos = tr->GetWorldPosition();

	auto move = go->AddComponent<MoveComponent>();
	move->SetSpeed(0); // current speed

	auto audio_idle = go->AddComponent<AudioSourceComponent>();
	audio_idle->loop = true;
	audio_idle->volume = .3f;
	auto audio_path_idle = "../assets/audio/player/idle.ogg";
	audio_idle->Play(audio_path_idle);

	auto audio_move = go->AddComponent<AudioSourceComponent>();
	audio_move->loop = true;
	audio_move->volume = .3f;

	move->MoveToggledEvent.Subscribe([audio_move](bool toggle)
	{
		auto audio_path_move = "../assets/audio/player/move.ogg";

		if (toggle) audio_move->Play(audio_path_move);
		else audio_move->Stop();
	});

	auto pursuit = go->AddComponent<PursuitComponent>();
	pursuit->vehicle = move;
	pursuit->maxSpeed = 3;
	pursuit->arrivalRange = .01f;
	pursuit->arrivalSlowingRangeOffset = .2f;
	pursuit->predict = false;
	pursuit->faceTarget = true;
	pursuit->angleOffset = 0;

	auto sprite = go->AddComponent<SpriteRendererComponent>();
	sprite->SetTexture("../assets/level/player/idle/idle_0.png");
	sprite->SetPixelsPerUnit(500);
	//sprite->RandomOffsetColor(.25f);

	auto anim = go->AddComponent<AnimatorComponent>();
	anim->sprite = sprite;

	Anim anim_idle{};
	anim_idle.animName = "Idle";
	anim_idle.pathPrefix = "../assets/level/player/idle/idle_";
	anim_idle.pathSuffix = ".png";
	anim_idle.frames = 1;
	anim_idle.fps = 1;
	anim_idle.loop = true;
	anim->AddAnim(anim_idle);

	Anim anim_move{};
	anim_move.animName = "Move";
	anim_move.pathPrefix = "../assets/level/player/move/move_";
	anim_move.pathSuffix = ".png";
	anim_move.frames = 2;
	anim_move.fps = 20;
	anim_move.loop = true;
	anim->AddAnim(anim_move);

	auto move_animator = go->AddComponent<MoveAnimComponent>();
	move_animator->Init(move, anim);
	move_animator->idleAnimName = "Idle";
	move_animator->moveAnimName = "Move";

	auto border = go->AddComponent<CameraBorderComponent>();

	auto coll = go->AddComponent<CircleColliderComponent>();
	coll->collideTags = { "Enemy", "EnemyBullet" };
	//coll->collideTags = { "null" };
	coll->radius = .1f;
	//coll->showGizmos = true;

	auto deflect = go->AddComponent<DeflectComponent>();
	deflect->deflectTags = { "EnemyBullet" };
	deflect->convertTag = { "PlayerBullet" };
	deflect->facingDir = { 0,1 };
	deflect->minDeflectDot = 0;
	deflect->recoilRange = { .1f,.2f };
	deflect->destroySelfOnFail = true;
	deflect->destroyOtherOnFail = true;

	deflect->DeflectEvent.Subscribe([pos]()
	{
		AudioManager::Play("PlayerDeflect", pos);
	});
	
	auto spawndestroy = go->AddComponent<SpawnOnDestroyComponent>();
	spawndestroy->prefabName = "PlayerExplode";
	spawndestroy->spawnCountRange = { 1,2 };

	//go->Destroy(2);

	return go;
}

// ===============================================================================

GameObject* PlayerExplodePrefab::CreateInstance()
{
	auto go = new GameObject("[GO] Player Explode");
	auto tr = go->GetTransform();
	auto pos = tr->GetWorldPosition();

	AudioManager::Play("Explode", pos);
	AudioManager::Play("PlayerDie", pos);
	AudioManager::Play("Subwoofer", pos);

	int num = 1;
	//int num = Random::Range(1, 4);
	//cout << go->name << ": number: " << num << endl;

	auto sprite = go->AddComponent<SpriteRendererComponent>();
	sprite->SetTexture("../assets/level/player/explode" + to_string(num) + "/explode fire_04.png");
	sprite->SetPixelsPerUnit(400);
	sprite->RandomOffsetColor(.25f);

	auto anim = go->AddComponent<AnimatorComponent>();
	anim->sprite = sprite;

	Anim anim_idle{};
	anim_idle.animName = "Idle";
	anim_idle.pathPrefix = "../assets/level/player/explode" + to_string(num) + "/explode fire_0";
	anim_idle.pathSuffix = ".png";
	anim_idle.frames = 10;
	anim_idle.fps = 15;
	anim_idle.loop = false;
	anim_idle.destroyOnFinish = true;
	anim->AddAnim(anim_idle);

	auto rand_tr = go->AddComponent<RandomTransformComponent>();
	rand_tr->randomRotate = true;
	rand_tr->randomScaleMult = true;

	return go;
}

// ===============================================================================

GameObject* EnemyPrefab::CreateInstance()
{
	auto go = new GameObject("[GO] Enemy");
	go->tag = "Enemy";

	auto tr = go->GetTransform();
	auto pos = tr->GetWorldPosition();

	AudioManager::Play("EnemySpawn", pos);

	auto move = go->AddComponent<MoveComponent>();
	move->SetSpeed(0); // current speed

	auto pursuit = go->AddComponent<PursuitComponent>();
	pursuit->vehicle = move;
	pursuit->maxSpeed = 1.5f;
	pursuit->arrival = true;
	pursuit->arrivalRange = 1;
	pursuit->arrivalSlowingRangeOffset = 1;
	pursuit->evade = false;
	pursuit->departure = true;
	pursuit->departureRange = .75f;
	pursuit->departureSlowingRangeOffset = .25f;
	pursuit->predict = true;
	pursuit->maintainDistance = true;
	pursuit->maintainRangeOffset = .25f;
	pursuit->faceTarget = true;
	pursuit->angleOffset = 0;

	int num = Random::Range(1, 3);
	cout << go->name << ": number: " << num << endl;

	auto sprite = go->AddComponent<SpriteRendererComponent>();
	sprite->SetTexture("../assets/level/enemies/enemy" + to_string(num) + "/idle/idle_0.png");
	sprite->SetPixelsPerUnit(300);
	sprite->RandomOffsetColor(.25f);

	auto anim = go->AddComponent<AnimatorComponent>();
	anim->sprite = sprite;

	Anim anim_idle{};
	anim_idle.animName = "Idle";
	anim_idle.pathPrefix = "../assets/level/enemies/enemy" + to_string(num) + "/idle/idle_";
	anim_idle.pathSuffix = ".png";
	anim_idle.frames = 1;
	anim_idle.fps = 1;
	anim_idle.loop = true;
	anim->AddAnim(anim_idle);

	Anim anim_move{};
	anim_move.animName = "Move";
	anim_move.pathPrefix = "../assets/level/enemies/enemy" + to_string(num) + "/move/move_";
	anim_move.pathSuffix = ".png";
	anim_move.frames = 10;
	anim_move.fps = 20;
	anim_move.loop = true;
	anim->AddAnim(anim_move);

	auto move_animator = go->AddComponent<MoveAnimComponent>();
	move_animator->Init(move, anim);
	move_animator->idleAnimName = "Idle";
	move_animator->moveAnimName = "Move";

	// ===============================================================================

	auto firepoint = new GameObject("[GO] Enemy Firepoint");
	auto firepoint_tr = firepoint->GetTransform();
	firepoint_tr->SetParent(tr);
	firepoint_tr->SetLocalPosition(0, .1f);

	// ===============================================================================

	auto shoot = go->AddComponent<ShootComponent>();
	shoot->autoFire = true;
	shoot->prefabName = "EnemyBullet";
	shoot->muzzlePrefabName = "EnemyMuzzle";
	shoot->firepoint = firepoint_tr;
	shoot->firepointDir = { 0,1 };
	shoot->angleOffset = 0;
	shoot->inaccuracyRange = { -15,15 };
	shoot->recoilRange = { .15f,.25f };
	shoot->speed = 2;
	shoot->lifetime = 3;
	shoot->cooldownRange = { 1,2 };
	
	shoot->ShootEvent.Subscribe([pos]()
	{
		AudioManager::Play("EnemyShoot", pos);
	});

	auto spawndestroy = go->AddComponent<SpawnOnDestroyComponent>();
	spawndestroy->prefabName = "EnemyExplode";
	spawndestroy->spawnCountRange = { 1,2 };

	auto rand_tr = go->AddComponent<RandomTransformComponent>();
	rand_tr->randomScaleMult = true;

	auto coll = go->AddComponent<CircleColliderComponent>();
	coll->collideTags = { "Player", "PlayerBullet" };
	//coll->collideTags = { "null" };
	coll->radius = .1f;
	//coll->showGizmos = true;

	auto destroy = go->AddComponent<DestroyOnCollideComponent>();
	destroy->validTags = { "Player", "PlayerBullet" };
	destroy->destroySelf = true;
	destroy->destroyOther = true;

	//go->Destroy(3);

	return go;
}

// ===============================================================================

GameObject* EnemyMuzzlePrefab::CreateInstance()
{
	auto go = new GameObject("[GO] Enemy Muzzle");

	int num = Random::Range(1, 3);
	cout << go->name << ": number: " << num << endl;

	auto sprite = go->AddComponent<SpriteRendererComponent>();
	sprite->SetTexture("../assets/level/enemies/muzzle" + to_string(num) + "/0.png");
	sprite->SetPixelsPerUnit(300);
	sprite->RandomOffsetColor(.25f);

	auto anim = go->AddComponent<AnimatorComponent>();
	anim->sprite = sprite;

	Anim anim_idle{};
	anim_idle.animName = "Idle";
	anim_idle.pathPrefix = "../assets/level/enemies/muzzle" + to_string(num) + "/";
	anim_idle.pathSuffix = ".png";
	anim_idle.frames = num == 1 ? 4 : 5;
	anim_idle.fps = 20;
	anim_idle.loop = false;
	anim_idle.destroyOnFinish = true;
	anim->AddAnim(anim_idle);

	auto rand_tr = go->AddComponent<RandomTransformComponent>();
	rand_tr->randomScaleMult = true;

	return go;
}

// ===============================================================================

GameObject* EnemyBulletPrefab::CreateInstance()
{
	auto go = new GameObject("[GO] Enemy Bullet");
	go->tag = "EnemyBullet";

	auto move = go->AddComponent<MoveComponent>();
	move->SetSpeed(3);
	//move->SetDirection(??);
	move->faceMoveDirection = true;
	move->angleOffset = 0;

	int num = Random::Range(1, 3);
	cout << go->name << ": number: " << num << endl;

	auto sprite = go->AddComponent<SpriteRendererComponent>();
	sprite->SetTexture("../assets/level/enemies/bullet" + to_string(num) + "/idle_0.png");
	sprite->SetPixelsPerUnit(300);
	sprite->RandomOffsetColor(.25f);

	auto anim = go->AddComponent<AnimatorComponent>();
	anim->sprite = sprite;

	Anim anim_idle{};
	anim_idle.animName = "Idle";
	anim_idle.pathPrefix = "../assets/level/enemies/bullet" + to_string(num) + "/idle_";
	anim_idle.pathSuffix = ".png";
	anim_idle.frames = num == 1 ? 1 : 10;
	anim_idle.fps = 20;
	anim_idle.loop = true;
	anim->AddAnim(anim_idle);

	auto rand_tr = go->AddComponent<RandomTransformComponent>();
	rand_tr->randomScaleMult = true;

	auto coll = go->AddComponent<CircleColliderComponent>();
	coll->collideTags = { "Player", "Enemy" };
	//coll->collideTags = { "null" };
	coll->radius = .025f;
	//coll->showGizmos = true;

	//auto destroy = go->AddComponent<DestroyOnCollideComponent>();
	//destroy->validTags = { "Player", "Enemy" };

	auto spawncollide = go->AddComponent<SpawnOnCollideComponent>();
	spawncollide->prefabName = "EnemyBulletImpact";
	spawncollide->spawnCountRange = { 1,2 };

	auto spawndestroy = go->AddComponent<SpawnOnDestroyComponent>();
	spawndestroy->prefabName = "EnemyBulletImpact";
	spawndestroy->spawnCountRange = { 1,2 };

	//go->Destroy(.5f);

	return go;
}

// ===============================================================================

GameObject* EnemyBulletImpactPrefab::CreateInstance()
{
	auto go = new GameObject("[GO] Enemy Bullet Impact");

	//int num = Random::Range(1, 4);
	int num = 1;
	//cout << go->name << ": number: " << num << endl;

	auto sprite = go->AddComponent<SpriteRendererComponent>();
	sprite->SetTexture("../assets/level/enemies/bullet_impact" + to_string(num) + "/impact_0.png");
	sprite->SetPixelsPerUnit(300);
	sprite->RandomOffsetColor(.25f);

	auto anim = go->AddComponent<AnimatorComponent>();
	anim->sprite = sprite;

	Anim anim_idle{};
	anim_idle.animName = "Idle";
	anim_idle.pathPrefix = "../assets/level/enemies/bullet_impact" + to_string(num) + "/impact_";
	anim_idle.pathSuffix = ".png";
	anim_idle.frames = 5;
	anim_idle.fps = 15;
	anim_idle.loop = false;
	anim_idle.destroyOnFinish = true;
	anim->AddAnim(anim_idle);

	auto rand_tr = go->AddComponent<RandomTransformComponent>();
	rand_tr->randomRotate = true;
	rand_tr->randomScaleMult = true;

	return go;
}

// ===============================================================================

GameObject* EnemyExplodePrefab::CreateInstance()
{
	auto go = new GameObject("[GO] Enemy Explode");
	auto tr = go->GetTransform();
	auto pos = tr->GetWorldPosition();

	AudioManager::Play("Explode", pos);

	int num = Random::Range(1, 4);
	cout << go->name << ": number: " << num << endl;

	auto sprite = go->AddComponent<SpriteRendererComponent>();
	sprite->SetTexture("../assets/level/enemies/explode" + to_string(num) + "/3.png");
	sprite->SetPixelsPerUnit(400);
	sprite->RandomOffsetColor(.25f);

	auto anim = go->AddComponent<AnimatorComponent>();
	anim->sprite = sprite;

	Anim anim_idle{};
	anim_idle.animName = "Idle";
	anim_idle.pathPrefix = "../assets/level/enemies/explode" + to_string(num) + "/";
	anim_idle.pathSuffix = ".png";
	anim_idle.frames = 10;
	anim_idle.fps = 15;
	anim_idle.loop = false;
	anim_idle.destroyOnFinish = true;
	anim->AddAnim(anim_idle);

	auto rand_tr = go->AddComponent<RandomTransformComponent>();
	rand_tr->randomRotate = true;
	rand_tr->randomScaleMult = true;

	return go;
}

// ===============================================================================

GameObject* EnemySpawnerPrefab::CreateInstance()
{
	auto go = new GameObject("[GO] Enemy Spawner");

	auto spawner = go->AddComponent<EnemySpawnerComponent>();
	spawner->prefabName = "Enemy";
	spawner->maxEnemies = 5;
	spawner->spawnrateRange = { 2,5 };
	//spawner->target = ???;
	spawner->expandOffset = .1f;

	return go;
}

// ===============================================================================

GameObject* LoseUIPrefab::CreateInstance()
{
	auto go = new GameObject("[GO] Lose UI");
	auto tr = go->GetTransform();
	tr->TranslateLocal(0, .1f);

	auto pos = tr->GetWorldPosition();

	AudioManager::Play("Lose", pos);
	AudioManager::Play("LoseAppear", pos);

	int num = Random::Range(1, 15);
	cout << go->name << ": number: " << num << endl;

	auto sprite = go->AddComponent<SpriteRendererComponent>();
	sprite->SetTexture("../assets/ui/lose/striplose" + to_string(num) + "/striplose_0.png");
	sprite->SetPixelsPerUnit(165);
	sprite->SetZIndex(10);
	//sprite->RandomOffsetColor(.25f);

	auto anim = go->AddComponent<AnimatorComponent>();
	anim->sprite = sprite;

	Anim anim_idle{};
	anim_idle.animName = "Idle";
	anim_idle.pathPrefix = "../assets/ui/lose/striplose" + to_string(num) + "/striplose_0";
	anim_idle.pathSuffix = ".png";
	anim_idle.frames = 10;
	anim_idle.fps = 15;
	anim_idle.loop = true;
	anim->AddAnim(anim_idle);

	// ===============================================================================

	auto retry = PrefabManager::Instantiate("RetryButton");
	auto retry_tr = retry->GetTransform();
	retry_tr->SetParent(tr);
	retry_tr->TranslateLocal(-.25f, -.5f);

	auto menu = PrefabManager::Instantiate("MenuButton");
	auto menu_tr = menu->GetTransform();
	menu_tr->SetParent(tr);
	menu_tr->TranslateLocal(.25f, -.5f);

	return go;
}

// ===============================================================================

GameObject* CreditsPrefab::CreateInstance()
{
	auto go = new GameObject("[GO] Credits");
	auto tr = go->GetTransform();

	auto sprite = go->AddComponent<SpriteRendererComponent>();
	sprite->SetTexture("../assets/credits/credits.png");
	sprite->SetPixelsPerUnit(400);

	tr->TranslateLocal(0, -sprite->GetSize().y);

	auto scroller = go->AddComponent<ScrollerComponent>();
	scroller->size = sprite->GetSize();
	scroller->speed = .3f;

	return go;
}

// ===============================================================================

GameObject* CreditsButtonPrefab::CreateInstance()
{
	auto go = new GameObject("[GO] Credits Button");

	auto tr = go->GetTransform();
	auto pos = tr->GetWorldPosition();

	auto sprite = go->AddComponent<SpriteRendererComponent>();
	sprite->SetTexture("../assets/credits/credits_button.png");
	sprite->SetPixelsPerUnit(300);

	auto button = go->AddComponent<ButtonComponent>();
	button->SetSprite(sprite);

	button->HoverEnterEvent.Subscribe([pos]()
	{
		AudioManager::Play("ButtonHover", pos);
	});

	button->PressEvent.Subscribe([pos]()
	{
		AudioManager::Play("ButtonClick", pos);
	});

	button->ReleaseEvent.Subscribe([]()
	{
		SceneStateMachine::LoadScene("CreditsScene");
	});
	
	auto follow = go->AddComponent<FollowCameraComponent>();
	follow->anchor = FollowCameraComponent::Anchor::BOTTOM_LEFT;
	follow->offset = { .25f,.1f };

	return go;
}

// ===============================================================================

GameObject* CreditsBackButtonPrefab::CreateInstance()
{
	auto go = new GameObject("[GO] Credits Back Button");

	auto tr = go->GetTransform();
	auto pos = tr->GetWorldPosition();

	auto sprite = go->AddComponent<SpriteRendererComponent>();
	sprite->SetTexture("../assets/credits/credits_back_button.png");
	sprite->SetPixelsPerUnit(300);

	auto button = go->AddComponent<ButtonComponent>();
	button->SetSprite(sprite);

	button->HoverEnterEvent.Subscribe([pos]()
	{
		AudioManager::Play("ButtonHover", pos);
	});

	button->PressEvent.Subscribe([pos]()
	{
		AudioManager::Play("ButtonClick", pos);
	});

	button->ReleaseEvent.Subscribe([]()
	{
		SceneStateMachine::LoadScene("MainMenuScene");
	});
	
	auto follow = go->AddComponent<FollowCameraComponent>();
	follow->anchor = FollowCameraComponent::Anchor::BOTTOM_LEFT;
	follow->offset = { .2f,.1f };

	return go;
}

