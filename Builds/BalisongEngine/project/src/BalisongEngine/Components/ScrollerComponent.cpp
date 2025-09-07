#include "ScrollerComponent.h"
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

ScrollerComponent::ScrollerComponent(GameObject* go, const string& comp_name) : BaseComponent(go, comp_name) {}
ScrollerComponent::~ScrollerComponent() {}

// ===============================================================================

void ScrollerComponent::Awake()
{
	Reset();
}

void ScrollerComponent::Update(float dt)
{
	auto pos = transform->GetWorldPosition();

	transform->TranslateLocal(0, speed*dt);

	float top_y = Camera::GetCorner(CameraCorner::TOP_RIGHT).y;

	auto half_size = size * .5f;

	if (pos.y >= top_y + half_size.y)
	{
		Reset();
	}
}

void ScrollerComponent::Reset()
{
	auto pos = transform->GetWorldPosition();

	float bottom_y = Camera::GetCorner(CameraCorner::BOTTOM_LEFT).y;

	auto half_size = size * .5f;

	transform->SetWorldPosition(pos.x, bottom_y - half_size.y);
}