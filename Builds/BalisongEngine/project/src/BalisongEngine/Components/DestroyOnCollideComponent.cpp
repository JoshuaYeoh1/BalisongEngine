#include "DestroyOnCollideComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
using namespace BalisongEngine;
using namespace BalisongEngineOCM;
using namespace BalisongEngineComponents;

#include <glm/glm.hpp>
using namespace glm;

#include <iostream>
using namespace std;

// ===============================================================================

DestroyOnCollideComponent::DestroyOnCollideComponent(GameObject* go, const string& comp_name) : BaseComponent(go, comp_name) {}
DestroyOnCollideComponent::~DestroyOnCollideComponent() {}

// ===============================================================================

void DestroyOnCollideComponent::OnCollisionEnter(GameObject* other)
{
    if (!other) return;
    if (!IsTagValid(other->tag)) return;
        
    if(destroySelf) gameObject->Destroy(.1f);
    if(destroyOther) other->Destroy(.1f);
}

// ===============================================================================

bool DestroyOnCollideComponent::IsTagValid(string tag)
{
    if (validTags.empty()) return true;

    for (auto t : validTags)
    {
        if (t == tag) return true;
    }
    return false;
}