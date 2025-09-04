#include "DeflectComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
using namespace BalisongEngine;
using namespace BalisongEngineOCM;
using namespace BalisongEngineComponents;

#include "MoveComponent.h"

#include "Random.h"
using namespace BalisongEngineFramework;

#include <glm/glm.hpp>
using namespace glm;

#include <iostream>
using namespace std;

// ===============================================================================

DeflectComponent::DeflectComponent(GameObject* go, const string& comp_name) : BaseComponent(go, comp_name) {}
DeflectComponent::~DeflectComponent() {}

// ===============================================================================

void DeflectComponent::OnCollisionEnter(GameObject* other)
{
    if (!other) return;
    if (!IsTagValid(other->tag)) return;
        
    auto move = other->GetComponent<MoveComponent>();
    if (!move) return;
    
    auto facing_dir = transform->TransformDirection(facingDir);

    float dot = glm::dot(facing_dir, move->GetDirection());

    if (dot <= minDeflectDot)
    {
        other->tag = convertTag;
        move->SetDirection(facing_dir);

        float recoil = GetRandom(recoilRange);
        transform->TranslateLocal(-facing_dir * recoil);

        DeflectEvent.Invoke();
    }
    else
    {
        if (destroySelfOnFail) gameObject->Destroy(.1f);
        if (destroyOtherOnFail) other->Destroy(.1f);
    }
}

// ===============================================================================

bool DeflectComponent::IsTagValid(string tag)
{
    if (deflectTags.size() == 0) return true;

    for (auto t : deflectTags)
    {
        if (t == tag) return true;
    }
    return false;
}

// ===============================================================================

float DeflectComponent::GetRandom(vec2 range)
{
    return Random::Range(range.x, range.y);
}