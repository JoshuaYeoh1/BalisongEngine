#include "AnimatorComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
using namespace BalisongEngine;
using namespace BalisongEngineOCM;
using namespace BalisongEngineComponents;

#include "SpriteRendererComponent.h"

#include <glm/glm.hpp>
using namespace glm;

#include <iostream>
using namespace std;

// ===============================================================================

AnimatorComponent::AnimatorComponent(GameObject* go, const string& comp_name) : BaseComponent(go, comp_name) {}

AnimatorComponent::~AnimatorComponent()
{
	AnimFinishedEvent.UnsubscribeAll();
}

// ===============================================================================

void AnimatorComponent::Update(float dt)
{
	if (!currentAnim) return;
	if (!sprite) return;

	// concatenate prefix + frame index + suffix
	string path = currentAnim->pathPrefix + to_string(currentFrameIndex) + currentAnim->pathSuffix;
	sprite->SetTexture(path);

	if (isPaused) return;
	if (currentAnim->fps <= 0) return;

	// wait for frame duration before continuing
	animTimer += dt;
	if (animTimer < currentAnim->GetFrameDuration()) return;
	animTimer = 0;

	// if not at the last frame
	if (currentFrameIndex < currentAnim->GetLastIndex())
	{
		currentFrameIndex++;
		return;
	}
	
	// if at the last frame
	TryFinishAnim();
}

// ===============================================================================

void AnimatorComponent::AddAnim(Anim new_anim)
{
	string anim_name = new_anim.animName;

	if (HasAnim(anim_name)) return;

	anims[anim_name] = new_anim;

	if (!currentAnim) SetAnim(anim_name);
}

void AnimatorComponent::RemoveAnim(const string& anim_name)
{
	auto it = anims.find(anim_name); // Direct lookup
	// if havent reached the end, means it found something
	if (it != anims.end())
	{
		anims.erase(it);
	}
}

// ===============================================================================

void AnimatorComponent::SetAnim(const string& anim_name)
{
	currentAnim = GetAnim(anim_name);
	currentFrameIndex = 0;
	animTimer = 0;

	cout << bothNames << ": Anim set to " << anim_name << endl;
}

Anim* AnimatorComponent::GetAnim(const string& anim_name)
{
	auto it = anims.find(anim_name); // Direct lookup
	// if havent reached the end, means it found something
	if (it != anims.end())
	{
		return &(it->second);
	}
	return nullptr;
}

Anim* AnimatorComponent::GetCurrentAnim()
{
	return currentAnim;
}

// ===============================================================================

bool AnimatorComponent::HasAnim(const string& anim_name)
{
	return GetAnim(anim_name) != nullptr;
}

// ===============================================================================

void AnimatorComponent::TryFinishAnim()
{
	// if looping
	if (currentAnim->loop)
	{
		currentFrameIndex = 0;
		return;
	}

	// if not looping
	AnimFinishedEvent.Invoke(currentAnim);

	if (currentAnim->HasNextAnim())
	{
		SetAnim(currentAnim->nextAnimName);
	}
	else if (currentAnim->destroyOnFinish)
	{
		gameObject->Destroy();
	}
	// stay on the last frame
	else currentFrameIndex = currentAnim->GetLastIndex();
}