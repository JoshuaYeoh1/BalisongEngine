#include "AudioManager.h"
#include "GameObject.h"
#include "PrefabManager.h"
#include "TransformComponent.h"
#include "AudioSourceComponent.h"
using namespace BalisongEngine;
using namespace BalisongEngineFramework;
using namespace BalisongEngineOCM;
using namespace BalisongEngineComponents;

#include <glm/glm.hpp>
using namespace glm;

#include <iostream>
using namespace std;

// ===============================================================================

unordered_map<string, Audio> AudioManager::audios;

// ===============================================================================

void AudioManager::AddAudio(const Audio& new_audio)
{
	if (new_audio.IsEmpty()) return;

	audios[new_audio.name] = new_audio;
}

void AudioManager::RemoveAudio(const string& audio_name)
{
	audios.erase(audio_name);
}

Audio* AudioManager::GetAudio(const string& audio_name)
{
	auto it = audios.find(audio_name);

	if (it != audios.end())
	{
		return &it->second;
	}
	return nullptr;
}

// ===============================================================================

AudioSourceComponent* AudioManager::Play(const string& audio_name, const vec2& pos)
{
    Audio* audio = GetAudio(audio_name);

    if (!audio) { cerr << "\n[AudioManager] Audio not found: " << audio_name << "\n\n"; return nullptr; }

	cout << "\n[AudioManager] Playing Audio: " << audio_name << "\n";
	cout << "[AudioManager] Path: " << audio->GetPath() << "\n";

	auto go = new GameObject("[GO] Audio");
	go->GetTransform()->SetWorldPosition(pos);

	auto source = go->AddComponent<AudioSourceComponent>();
    source->playOnAwake = false;
	source->Awake();
    source->loop = false;
    source->mute = false;

    source->volume = audio->GetVolume();
    source->stereoPan = audio->GetStereoPan();
    source->speed = audio->GetSpeed();

	source->spatialBlend = audio->spatialBlend;
	source->minDistance = audio->minDistance;
	source->maxDistance = audio->maxDistance;

	source->Update(0);

	source->Play(audio->GetPath());

    float length = source->GetLength();
    go->Destroy(length);

	return source;
}
