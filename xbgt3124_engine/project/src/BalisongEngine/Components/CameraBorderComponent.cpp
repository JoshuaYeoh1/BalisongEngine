#include "CameraBorderComponent.h"
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

CameraBorderComponent::CameraBorderComponent(GameObject* go, const string& comp_name) : BaseComponent(go, comp_name) {}
CameraBorderComponent::~CameraBorderComponent() {}

// ===============================================================================

void CameraBorderComponent::Update(float dt)
{
	if (!isActive) return;

	auto pos = transform->GetWorldPosition();

	auto positive = Camera::GetCorner(CameraCorner::TOP_RIGHT);
	auto negative = Camera::GetCorner(CameraCorner::BOTTOM_LEFT);

	auto min_x = negative.x - expandOffset;
	auto max_x = positive.x + expandOffset;
	auto min_y = negative.y - expandOffset;
	auto max_y = positive.y + expandOffset;

	bool is_in_border = pos.x >= min_x && pos.x <= max_x
					 && pos.y >= min_y && pos.y <= max_y;

	if (is_in_border) return;

	vec2 constrained_pos = pos;
	constrained_pos.x = clamp(pos.x, min_x, max_x);
	constrained_pos.y = clamp(pos.y, min_y, max_y);

	transform->SetWorldPosition(constrained_pos);
}
