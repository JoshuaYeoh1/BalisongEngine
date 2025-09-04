#include "FollowCameraComponent.h"
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

// ===============================================================================

FollowCameraComponent::FollowCameraComponent(GameObject* go, const string& comp_name) : BaseComponent(go, comp_name) {}
FollowCameraComponent::~FollowCameraComponent() {}

// ===============================================================================

void FollowCameraComponent::Update(float dt)
{
	Follow();
}

vec2 FollowCameraComponent::GetAnchor()
{
	auto center = Camera::GetPosition();

	auto negative = Camera::GetCorner(CameraCorner::BOTTOM_LEFT);
	auto positive = Camera::GetCorner(CameraCorner::TOP_RIGHT);

	switch (anchor)
	{
	case Anchor::CENTER: return center;
	case Anchor::TOP: return { center.x,positive.y };
	case Anchor::BOTTOM: return { center.x,negative.y };
	case Anchor::LEFT: return { negative.x,center.y };
	case Anchor::RIGHT: return { positive.x,center.y };
	case Anchor::TOP_LEFT: return { negative.x,positive.y };
	case Anchor::TOP_RIGHT: return positive;
	case Anchor::BOTTOM_LEFT: return negative;
	case Anchor::BOTTOM_RIGHT: return { positive.x,negative.y };
	}
}

void FollowCameraComponent::Follow()
{
	auto pos = GetAnchor();

	transform->SetWorldPosition(pos + offset);
}