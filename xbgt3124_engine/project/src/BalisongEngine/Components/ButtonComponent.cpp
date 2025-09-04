#include "ButtonComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
using namespace BalisongEngine;
using namespace BalisongEngineOCM;
using namespace BalisongEngineComponents;

#include "SpriteRendererComponent.h"

#include "Input.h"
using namespace BalisongEngineFramework;

#include "Camera.h"
using namespace BalisongEngineRenderer;

#include <glm/glm.hpp>
using namespace glm;

#include <iostream>
using namespace std;

// ===============================================================================

ButtonComponent::ButtonComponent(GameObject* go, const string& comp_name) : BaseComponent(go, comp_name) {}

ButtonComponent::~ButtonComponent()
{
	HoverEnterEvent.UnsubscribeAll();
	HoverExitEvent.UnsubscribeAll();
	PressEvent.UnsubscribeAll();
	ReleaseEvent.UnsubscribeAll();
	ReleaseCancelEvent.UnsubscribeAll();
}

// ===============================================================================

void ButtonComponent::Update(float dt)
{
	if (isActive)
	{
		if (!hasActivated)
		{
			hasActivated = true;
			ToggleActive(true);
		}
	}
	else
	{
		hasHovered = false;
		hasPressed = false;

		if (hasActivated)
		{
			hasActivated = false;
			ToggleActive(false);
		}
		return;
	}

	if (IsHovering())
	{
		if (!hasHovered)
		{
			hasHovered = true;
			HoverEnter();
		}

		if (!hasPressed)
		{
			if (Input::GetMouseDown(MouseCode::LEFT))
			{
				hasPressed = true;
				Press();
			}
		}
		else
		{
			if (Input::GetMouseUp(MouseCode::LEFT))
			{
				hasPressed = false;
				Release();
			}
		}
	}
	else
	{
		if (hasHovered)
		{
			hasHovered = false;
			HoverExit();
		}
	}

	if (hasPressed)
	{
		if (Input::GetMouseUp(MouseCode::LEFT))
		{
			hasPressed = false;
			ReleaseCancel();
		}
	}
}

// ===============================================================================

void ButtonComponent::HoverEnter()
{
	SetTint(hoverTint);
	SetTexture(hoverTexture);

	cout << bothNames << ": HoverEnterEvent\n";

	HoverEnterEvent.Invoke();
}

void ButtonComponent::HoverExit()
{
	RevertTint();
	RevertTexture();

	cout << bothNames << ": HoverExitEvent\n";

	HoverExitEvent.Invoke();
}

void ButtonComponent::Press()
{
	SetTint(pressTint);
	SetTexture(pressTexture);

	cout << bothNames << ": PressEvent\n";

	PressEvent.Invoke();
}

void ButtonComponent::Release()
{
	SetTint(hoverTint);
	SetTexture(hoverTexture);

	cout << bothNames << ": ReleaseEvent\n";

	ReleaseEvent.Invoke();
}

void ButtonComponent::ReleaseCancel()
{
	RevertTint();
	RevertTexture();

	cout << bothNames << ": ReleaseCancelEvent\n";

	ReleaseCancelEvent.Invoke();
}

void ButtonComponent::ToggleActive(bool toggle)
{
	if (toggle)
	{
		RevertTint();
		RevertTexture();
	}
	else
	{
		SetTint(inactiveTint);
		SetTexture(inactiveTexture);
	}

	cout << bothNames << ": ToggleActiveEvent: " << toggle << endl;

	ToggleActiveEvent.Invoke(toggle);
}

// ===============================================================================

void ButtonComponent::SetButtonSize(vec2 to)
{
	buttonSize = to;
}
void ButtonComponent::SetButtonSize(float x, float y)
{
	SetButtonSize({ x,y });
}
vec2 ButtonComponent::GetButtonSize() const
{
	return buttonSize;
}

// ===============================================================================

void ButtonComponent::SetButtonOffset(vec2 to)
{
	buttonOffset = to;
}
void ButtonComponent::SetButtonOffset(float x, float y)
{
	SetButtonOffset({ x,y });
}
vec2 ButtonComponent::GetButtonOffset() const
{
	return buttonOffset;
}

// ===============================================================================

bool ButtonComponent::IsHovering()
{
	auto mouse_pos = Input::GetMousePosition();
	auto mouse_world_pos = Camera::ScreenToWorld(mouse_pos);

	//cout << "Mouse Pos: " << mouse_pos.x << "," << mouse_pos.y << endl;
	//cout << "Mouse World Pos: " << mouse_world_pos.x << "," << mouse_world_pos.y << "," << mouse_world_pos.z << endl;

	return IsInButton(mouse_world_pos);
}

// ===============================================================================

bool ButtonComponent::IsInButton(vec2 target_pos)
{
	auto pos = transform->GetWorldPosition() + buttonOffset;

	auto scale = buttonSize * transform->GetWorldScale();
	auto half_size = scale * .5f;

	return
		(target_pos.x > pos.x - half_size.x &&
		target_pos.x <= pos.x + half_size.x)
		&&
		(target_pos.y > pos.y - half_size.y &&
		target_pos.y <= pos.y + half_size.y);
}

// ===============================================================================

void ButtonComponent::SetSprite(SpriteRendererComponent* to)
{
	sprite = to;
	if (!sprite) return;

	SetButtonSize(sprite->GetSize());
	defaultTint = sprite->GetTint();
	defaultTexture = sprite->GetCurrentPath();
}

// ===============================================================================

void ButtonComponent::SetTint(vec4 to)
{
	if (!sprite) return;

	sprite->SetTint(to);
}
void ButtonComponent::RevertTint()
{
	SetTint(defaultTint);
}

// ===============================================================================

void ButtonComponent::SetTexture(string to)
{
	if (!sprite) return;
	if (to.empty()) return;

	sprite->SetTexture(to);
}

void ButtonComponent::RevertTexture()
{
	SetTexture(defaultTexture);
}