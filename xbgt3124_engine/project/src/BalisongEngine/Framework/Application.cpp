#include "Application.h" // AppWindow included
using namespace BalisongEngine;

#include "Allocator.h"
using namespace BalisongEngineAllocator;

#include "TransformComponent.h"
#include "AudioSourceComponent.h"
using namespace BalisongEngineComponents;

#include "TimeEngine.h"
#include "Input.h"
#include "Random.h"
#include "AudioManager.h"
using namespace BalisongEngineFramework;

#include "GameObject.h"
#include "Prefabs.h"
#include "PrefabManager.h"
using namespace BalisongEngineOCM;

#include "Renderer.h"
#include "Camera.h"
using namespace BalisongEngineRenderer;

#include "SceneStateMachine.h"
#include "SplashScene.h"
#include "MainMenuScene.h"
#include "LevelScene.h"
#include "CreditsScene.h"
using namespace BalisongEngineScenes;

#include <string>
#include <iostream>
using namespace std;

// ====================================================================

// Actually define the static Application instance variable
Application* Application::instance;

// ====================================================================

int Application::Init(int width, int height, string title)
{
	AppWindowData data(width, height, title);

	int result = window.Init(data);

	if (result == 1)
	{
		isRunning = true;
		targetFrameRate = 0;
		frameTime = 0.0f;
		instance = this;

		window.SetWindowEventCallback([this](AppWindowEventType eventType, void* payload)
		{
			OnReceiveAppWindowEvent(eventType, payload);
		});
	}

	return result;
}

// ====================================================================

static string GetMusic()
{
	switch (Random::Range(1, 3))
	{
	case 1: return "../assets/audio/music/masseffect_wards.ogg";
	case 2: return "../assets/audio/music/worms_space.ogg";
	}
	return "";
}

// ====================================================================

void Application::Run()
{
	// Input ===============================================================================

	Input::Init(&window);

	// Renderer ===============================================================================
	
	Renderer::Init();

	if (!Renderer::Load())
	{
		cerr << "Failed to load OpenGL functions with glad.\n";
		return;
	}

	Renderer::SetViewport(0, 0, GetWindowWidth(), GetWindowHeight());

	// Camera ===============================================================================

	CameraConfig cfg;
	Camera::Init(cfg, GetWindowWidth(), GetWindowHeight());

	// Prefabs ===============================================================================
	
	PrefabManager::AddPrefab("Title", new TitlePrefab());
	PrefabManager::AddPrefab("PlayButton", new PlayButtonPrefab());
	PrefabManager::AddPrefab("RetryButton", new RetryButtonPrefab());
	PrefabManager::AddPrefab("MenuButton", new MenuButtonPrefab());
	PrefabManager::AddPrefab("Tutorial", new TutorialPrefab());
	PrefabManager::AddPrefab("Mouse", new MousePrefab());
	PrefabManager::AddPrefab("Player", new PlayerPrefab());
	PrefabManager::AddPrefab("PlayerExplode", new PlayerExplodePrefab());
	PrefabManager::AddPrefab("Enemy", new EnemyPrefab());
	PrefabManager::AddPrefab("EnemyMuzzle", new EnemyMuzzlePrefab());
	PrefabManager::AddPrefab("EnemyBullet", new EnemyBulletPrefab());
	PrefabManager::AddPrefab("EnemyBulletImpact", new EnemyBulletImpactPrefab());
	PrefabManager::AddPrefab("EnemyExplode", new EnemyExplodePrefab());
	PrefabManager::AddPrefab("EnemySpawner", new EnemySpawnerPrefab());
	PrefabManager::AddPrefab("LoseUI", new LoseUIPrefab());
	PrefabManager::AddPrefab("Credits", new CreditsPrefab());
	PrefabManager::AddPrefab("CreditsButton", new CreditsButtonPrefab());
	PrefabManager::AddPrefab("CreditsBackButton", new CreditsBackButtonPrefab());

	// Scenes ===============================================================================

	SceneStateMachine::AddScene<SplashScene>();
	SceneStateMachine::AddScene<MainMenuScene>();
	SceneStateMachine::AddScene<LevelScene>();
	SceneStateMachine::AddScene<CreditsScene>();
	SceneStateMachine::LoadScene("SplashScene");

	// Audios ===============================================================================
	
	Audio audio {};

	audio.name = "EnemyShoot";
	audio.pathPrefix = "../assets/audio/enemy/shoot/pew (";
	audio.pathSuffix = ").ogg";
	audio.paths = 30;
	audio.volumeRange = { 1,1 };
	audio.stereoPanRange = { 0,0 };
	audio.speedRange = { .8f,1.2f };
	audio.spatialBlend = true;
	audio.minDistance = 1.75f;
	audio.maxDistance = 3.5f;
	AudioManager::AddAudio(audio);

	audio.name = "EnemySpawn";
	audio.pathPrefix = "../assets/audio/enemy/spawn";
	audio.pathSuffix = ".ogg";
	audio.paths = 1;
	audio.volumeRange = { 1,1 };
	audio.stereoPanRange = { 0,0 };
	audio.speedRange = { .8f,1.2f };
	audio.spatialBlend = true;
	audio.minDistance = 1.75f;
	audio.maxDistance = 3.5f;
	AudioManager::AddAudio(audio);

	audio.name = "Explode";
	audio.pathPrefix = "../assets/audio/explode/boom (";
	audio.pathSuffix = ").ogg";
	audio.paths = 39;
	audio.volumeRange = { 1,1 };
	audio.stereoPanRange = { 0,0 };
	audio.speedRange = { .8f,1.2f };
	audio.spatialBlend = true;
	audio.minDistance = 1.75f;
	audio.maxDistance = 3.5f;
	AudioManager::AddAudio(audio);

	audio.name = "PlayerDeflect";
	audio.pathPrefix = "../assets/audio/player/deflect/deflect (";
	audio.pathSuffix = ").ogg";
	audio.paths = 22;
	audio.volumeRange = { 1,1 };
	audio.stereoPanRange = { 0,0 };
	audio.speedRange = { .8f,1.2f };
	audio.spatialBlend = true;
	audio.minDistance = 1.75f;
	audio.maxDistance = 3.5f;
	AudioManager::AddAudio(audio);

	audio.name = "PlayerDie";
	audio.pathPrefix = "../assets/audio/player/die";
	audio.pathSuffix = ".ogg";
	audio.paths = 1;
	audio.volumeRange = { 1,1 };
	audio.stereoPanRange = { 0,0 };
	audio.speedRange = { .8f,1.2f };
	audio.spatialBlend = true;
	audio.minDistance = 1.75f;
	audio.maxDistance = 3.5f;
	AudioManager::AddAudio(audio);

	audio.name = "ButtonClick";
	audio.pathPrefix = "../assets/audio/ui/button/down/click";
	audio.pathSuffix = ".ogg";
	audio.paths = 1;
	audio.volumeRange = { 1,1 };
	audio.stereoPanRange = { 0,0 };
	audio.speedRange = { .8f,1.2f };
	audio.spatialBlend = true;
	audio.minDistance = 1.75f;
	audio.maxDistance = 3.5f;
	AudioManager::AddAudio(audio);

	audio.name = "ButtonHover";
	audio.pathPrefix = "../assets/audio/ui/button/hover/hover (";
	audio.pathSuffix = ").ogg";
	audio.paths = 4;
	audio.volumeRange = { 1,1 };
	audio.stereoPanRange = { 0,0 };
	audio.speedRange = { .8f,1.2f };
	audio.spatialBlend = true;
	audio.minDistance = 1.75f;
	audio.maxDistance = 3.5f;
	AudioManager::AddAudio(audio);

	audio.name = "ButtonPlay";
	audio.pathPrefix = "../assets/audio/ui/button/play/play (";
	audio.pathSuffix = ").ogg";
	audio.paths = 2;
	audio.volumeRange = { 1,1 };
	audio.stereoPanRange = { 0,0 };
	audio.speedRange = { .8f,1.2f };
	audio.spatialBlend = true;
	audio.minDistance = 1.75f;
	audio.maxDistance = 3.5f;
	AudioManager::AddAudio(audio);

	audio.name = "Lose";
	audio.pathPrefix = "../assets/audio/ui/lose/lose";
	audio.pathSuffix = ".ogg";
	audio.paths = 1;
	audio.volumeRange = { 1,1 };
	audio.stereoPanRange = { 0,0 };
	audio.speedRange = { .8f,1.2f };
	audio.spatialBlend = false;
	audio.minDistance = 1.75f;
	audio.maxDistance = 3.5f;
	AudioManager::AddAudio(audio);

	audio.name = "LoseAppear";
	audio.pathPrefix = "../assets/audio/ui/lose/appear";
	audio.pathSuffix = ".ogg";
	audio.paths = 1;
	audio.volumeRange = { 1,1 };
	audio.stereoPanRange = { 0,0 };
	audio.speedRange = { .8f,1.2f };
	audio.spatialBlend = false;
	audio.minDistance = 1.75f;
	audio.maxDistance = 3.5f;
	AudioManager::AddAudio(audio);

	audio.name = "Subwoofer";
	audio.pathPrefix = "../assets/audio/ui/subwoofer/subwoofer (";
	audio.pathSuffix = ").ogg";
	audio.paths = 12;
	audio.volumeRange = { 1,1 };
	audio.stereoPanRange = { 0,0 };
	audio.speedRange = { .8f,1.2f };
	audio.spatialBlend = false;
	audio.minDistance = 1.75f;
	audio.maxDistance = 3.5f;
	AudioManager::AddAudio(audio);

	// Music ===============================================================================
	 
	// dont use game object because it will be deleted on scene change
	auto global_music = new AudioSourceComponent(nullptr);
	global_music->playOnAwake = false;
	global_music->Awake();
	global_music->loop = false; // to check if finished
	global_music->volume = 1;
	global_music->stereoPan = 0;
	global_music->speed = 1;
	global_music->spatialBlend = false;

	// ===============================================================================

	while (isRunning)
	{
		// Music Shuffle ===============================================================================
		
		if(!global_music->IsPlaying()) global_music->Play(GetMusic());
		 
		// Timing ===============================================================================

		TimeEngine::ProcessTime(frameTime);

		// Input Processing ===============================================================================

		Input::Process();
		
		// Updates ===============================================================================

		SceneStateMachine::Update(TimeEngine::GetDeltaTime());

		AppHotkeys();
		
		// Rendering ===============================================================================

		Renderer::ClearFramebuffer();
		Renderer::BeginFrame();

		SceneStateMachine::Render();

		Renderer::EndFrame();
		
		// Finalize ===============================================================================

		window.Update();
	}

	Allocator::ReleaseAllUnusedResources();

	// Stop Music ===============================================================================

	global_music->Stop();
	global_music->OnDestroy();
	delete global_music;
}

// ====================================================================

void Application::CleanUp()
{
	// empty
	// window will be automatically cleaned
	// when main program exits due to
	// window being an object on the stack.
}

// ====================================================================

void Application::SetTargetFrameRate(unsigned int frame_rate)
{
	instance->targetFrameRate = frame_rate;
	instance->frameTime = frame_rate > 0 ? 1.0f / frame_rate : 0.0f;

	if(frame_rate>0) cout << "FPS: " << frame_rate << endl;
	else cout << "FPS: Unlimited" << endl;
}

// ====================================================================

void Application::Quit()
{
	instance->isRunning = false;
}

// ====================================================================

void Application::OnReceiveAppWindowEvent(AppWindowEventType& event_type, void* payload)
{
	switch (event_type)
	{

	case AppWindowEventType::CLOSE:
	{
		cout << "Window Close Event" << endl;
		isRunning = false;
	}
	break;

	case AppWindowEventType::RESIZE:
	{
		ResizeEventData* resize_data = static_cast<ResizeEventData*>(payload);

		if (resize_data == nullptr) return;

		int new_width = resize_data->width;
		int new_height = resize_data->height;

		Camera::Recalculate(new_width, new_height);

		Renderer::SetViewport(0, 0, new_width, new_height);

		cout << "Resized to: " << new_width << "x" << new_height << endl;
	}
	break;

	}
}

// ====================================================================

void Application::AppHotkeys()
{
	// press esc to close
	if (Input::GetKey(KeyCode::ESCAPE))
	{
		Application::Quit();
	}

	// frame limiting with 12345
	if (Input::GetKeyDown(KeyCode::ALPHA_1))
	{
		SetTargetFrameRate(10);
	}
	if (Input::GetKeyDown(KeyCode::ALPHA_2))
	{
		SetTargetFrameRate(20);
	}
	if (Input::GetKeyDown(KeyCode::ALPHA_3))
	{
		SetTargetFrameRate(30);
	}
	if (Input::GetKeyDown(KeyCode::ALPHA_4))
	{
		SetTargetFrameRate(60);
	}
	if (Input::GetKeyDown(KeyCode::ALPHA_5))
	{
		SetTargetFrameRate(0); // uncapped
	}

	// application screen size
	if (Input::GetKeyDown(KeyCode::F1))
	{
		SetWindowSize(200, 150);
	}
	if (Input::GetKeyDown(KeyCode::F2))
	{
		SetWindowSize(400, 300);
	}
	if (Input::GetKeyDown(KeyCode::F3))
	{
		SetWindowSize(800, 600);
	}
	if (Input::GetKeyDown(KeyCode::F4))
	{
		SetWindowSize(1280, 720);
	}

	// current screen size
	if (Input::GetKeyDown(KeyCode::SPACE))
	{
		cout << "Resolution: " << GetWindowWidth() << "x" << GetWindowHeight() << endl;
	}
}