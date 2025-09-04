#include "FollowMouseComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
using namespace BalisongEngine;
using namespace BalisongEngineOCM;
using namespace BalisongEngineComponents;

#include "Input.h"
using namespace BalisongEngineFramework;

#include "Camera.h"
using namespace BalisongEngineRenderer;

#include <glm/glm.hpp>
using namespace glm;

#include <iostream>
using namespace std;

// ===============================================================================

FollowMouseComponent::FollowMouseComponent(GameObject* go, const string& comp_name) : BaseComponent(go, comp_name) {}
FollowMouseComponent::~FollowMouseComponent() {}

// ===============================================================================

void FollowMouseComponent::Update(float dt)
{
	if (!isActive) return;

	auto mouse_pos = Input::GetMousePosition();
	mouse_pos = Camera::ScreenToWorld(mouse_pos);

	transform->SetWorldPosition(mouse_pos);
}
