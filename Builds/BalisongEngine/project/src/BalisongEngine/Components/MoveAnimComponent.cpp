#include "MoveAnimComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
using namespace BalisongEngine;
using namespace BalisongEngineOCM;
using namespace BalisongEngineComponents;

#include "MoveComponent.h"
#include "AnimatorComponent.h"

#include <glm/glm.hpp>
using namespace glm;

#include <iostream>
using namespace std;

// ===============================================================================

MoveAnimComponent::MoveAnimComponent(GameObject* go, const string& comp_name) : BaseComponent(go, comp_name) {}
MoveAnimComponent::~MoveAnimComponent() {}

// ===============================================================================

void MoveAnimComponent::Init(MoveComponent* move_comp, AnimatorComponent* anim_comp)
{
	moveComp = move_comp;
	animComp = anim_comp;

	OnMoveToggled_id = moveComp->MoveToggledEvent.Subscribe(this, &MoveAnimComponent::OnMoveToggled);
	// IT MUST BE &MoveAnimComponent::OnMoveToggled, NOT ONLY &OnMoveToggled
}

// ===============================================================================

void MoveAnimComponent::OnMoveToggled(bool toggle)
{
	if(animComp)
	animComp->SetAnim(toggle ? moveAnimName : idleAnimName);
}

// ===============================================================================

void MoveAnimComponent::OnDestroyComponent()
{
	if (moveComp)
		moveComp->MoveToggledEvent.Unsubscribe(OnMoveToggled_id);
}