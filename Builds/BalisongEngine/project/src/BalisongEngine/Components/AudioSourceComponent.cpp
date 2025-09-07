#include "AudioSourceComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
using namespace BalisongEngine;
using namespace BalisongEngineOCM;
using namespace BalisongEngineComponents;

#include "Camera.h"
using namespace BalisongEngineRenderer;

#include <glm/glm.hpp>
using namespace glm;

#include <iostream>
using namespace std;

#include <irrKlang.h>
using namespace irrklang;

// ===============================================================================

AudioSourceComponent::AudioSourceComponent(GameObject* go, const string& comp_name) : BaseComponent(go, comp_name) {}
AudioSourceComponent::~AudioSourceComponent() {}

// ===============================================================================

void AudioSourceComponent::Awake()
{
    if (!soundEngine) soundEngine = createIrrKlangDevice(); // init irrklang engine

    if (!soundEngine) cout << "\n\nFailed to initialize irrKlang engine!\n\n";
    
    if (playOnAwake) Play();

	//soLoud.init();
}

// ===============================================================================

void AudioSourceComponent::Play()
{
    Stop();

    if (!soundEngine) return;

    currentSound = soundEngine->play2D(path.c_str(), loop, true); // pause first
    if (!currentSound) return;

    ApplySettings(currentSound);

    currentSound->setIsPaused(false); // start playing

    //sample.load(path.c_str());
    //handle = soLoud.play(sample);
}

void AudioSourceComponent::Play(string path2)
{
    path = path2;
    Play();
}

// ===============================================================================

void AudioSourceComponent::PlayOneShot()
{
    if (!soundEngine) return;

    auto sound = soundEngine->play2D(path.c_str(), false, true); // no loop, pause first
    if (!sound) return;

    ApplySettings(sound);

    sound->setIsPaused(false); // start playing
    sound->drop(); // release sound resource

    //sample.load(path.c_str());
    //handle = soLoud.play(sample);
    //soLoud.setLooping(handle, false); // no loop
}

void AudioSourceComponent::PlayOneShot(string path2)
{
    path = path2;
    PlayOneShot();
}

// ===============================================================================

bool AudioSourceComponent::IsPlaying()
{
    return currentSound && !currentSound->isFinished();

    //return handle != -1 && soLoud.getActiveVoiceCount() > 0;
}

float AudioSourceComponent::GetLength()
{
    if (!currentSound) return 0.0f;
    // milliseconds to seconds
    float seconds = static_cast<float>(currentSound->getPlayLength()) / 1000.0f;
    return seconds * speed;
}

// ===============================================================================

void AudioSourceComponent::Stop()
{
    if (!currentSound) return;

    currentSound->stop();
    currentSound->drop(); // release sound resource
    currentSound = nullptr;

    //if (handle != -1)
    //{
    //    handle = -1; // reset handle
    //    //soloud.stop(handle);
    //}
}

// ===============================================================================

void AudioSourceComponent::ApplySettings(ISound* sound)
{
    if (!sound) return;

    float vol = clamp(volume * spatialVolume, 0.0f, 1.0f);
    float pan = clamp(stereoPan * spatialStereoPan, -1.0f, 1.0f);
    speed = glm::max(speed, .01f);

    sound->setVolume(mute ? 0 : vol);
    sound->setPan(pan);
    sound->setPlaybackSpeed(speed);
}

// ===============================================================================

void AudioSourceComponent::Update(float dt)
{
    auto pos = transform ? transform->GetWorldPosition() : vec2(0);

    UpdateSpatialVolume(pos);
    UpdateSpatialStereoPan(pos);

    if (currentSound)
    ApplySettings(currentSound);
}

// ===============================================================================

void AudioSourceComponent::UpdateSpatialVolume(vec2 pos)
{
    if (!spatialBlend) { spatialVolume = 1; return; }

    if(minDistance == 0 && maxDistance == 0) { spatialVolume = 0; return; }
    
    auto cam_pos = Camera::GetPosition();
    float distance = glm::distance(pos, cam_pos);

    float distance_offset = distance - minDistance;
    float distance_max_offset = maxDistance - minDistance;

    float distance01 = glm::clamp(distance_offset / distance_max_offset, 0.0f, 1.0f);

    // lerp
    spatialVolume = 1.0f + distance01 * (0.0f - 1.0f);
}

// ===============================================================================

void AudioSourceComponent::UpdateSpatialStereoPan(vec2 pos)
{
    if (!spatialBlend) { spatialStereoPan = 0; return; }

    float min_x = Camera::GetCorner(CameraCorner::BOTTOM_LEFT).x;
    float max_x = Camera::GetCorner(CameraCorner::TOP_RIGHT).x;

    if (min_x == max_x) { spatialStereoPan = 0; return; }

    auto clamped_x = clamp(pos.x, min_x, max_x);

    float x_offset = clamped_x - min_x;
    float x_max_offset = max_x - min_x;

    float pan_nomalized = x_offset / x_max_offset * 2.0f - 1.0f;

    spatialStereoPan = glm::clamp(pan_nomalized, -1.0f, 1.0f);
}

// ===============================================================================

void AudioSourceComponent::OnDestroy()
{
    Stop();

    if (soundEngine)
    {
        soundEngine->drop(); // cleanup irrklang engine
        soundEngine = nullptr;
    }
    //soLoud.deinit();
}

// Old
//soLoud.setLooping(handle, loop);
//soLoud.setVolume(handle, mute ? 0 : volume);
//soLoud.setRelativePlaySpeed(handle, speed);
//soLoud.setPan(handle, stereoPan);