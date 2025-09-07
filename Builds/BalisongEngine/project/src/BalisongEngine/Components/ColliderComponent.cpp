#include "ColliderComponent.h"
#include "GameObject.h"
#include "GameObjectRefSet.h"
#include "TransformComponent.h"
using namespace BalisongEngine;
using namespace BalisongEngineOCM;
using namespace BalisongEngineComponents;

#include "ColliderManager.h"

#include <glm/glm.hpp>
using namespace glm;

#include <iostream>
using namespace std;

// ===============================================================================

ColliderComponent::ColliderComponent(GameObject* go, const string& comp_name) : BaseComponent(go, comp_name) {}
ColliderComponent::~ColliderComponent() {}

// ===============================================================================

void ColliderComponent::Awake()
{
	ColliderManager::Add(this);
}

// ===============================================================================

vec2 ColliderComponent::GetCenter() const
{
    return transform->GetWorldPosition() + offset;
}

// ===============================================================================

bool ColliderComponent::IsTagValid(string tag) const
{
    if (collideTags.empty()) return true;

    for (auto t : collideTags)
    {
        if (t == tag) return true;
    }
    return false;
}

// ===============================================================================

void ColliderComponent::OnCollideWith(GameObject* other)
{
    if (!other) return;
    if (!IsTagValid(other->tag)) return;
        
    currentColliders.Add(other);
}

// ===============================================================================

void ColliderComponent::UpdateCollisions()
{
    CheckEnter();
    CheckStay();
    CheckExit();

    // prepare for the next round of update
    previousColliders = currentColliders;
    currentColliders.RemoveAll();
}

// ===============================================================================

void ColliderComponent::CheckEnter()
{
    for(int i = 0; i< currentColliders.Count(); i++)
    {
        auto current = currentColliders.Get(i);
        if (!current) continue;

        // if in current but not in previous
        if (!previousColliders.Contains(current))
        {
            // if none previously, this is the first
            if (previousColliders.IsEmpty())
            {
                gameObject->OnCollisionFirstEnter(current);
            }

            gameObject->OnCollisionEnter(current);
        }
    }
}

void ColliderComponent::CheckStay()
{
    if (!IsColliding()) return;

    gameObject->OnCollisionStay(currentColliders.GetAll());
}

void ColliderComponent::CheckExit()
{
    for (int i = 0; i < previousColliders.Count(); i++)
    {
        auto previous = previousColliders.Get(i);

        // if in previous but not in current
        // or its null because got destroyed
        if (!currentColliders.Contains(previous) || !previous)
        {
            gameObject->OnCollisionExit(previous);

            // if none currently, this is the last
            if (currentColliders.IsEmpty())
            {
                gameObject->OnCollisionLastExit(previous);
            }
        }
    }
}

// ===============================================================================

bool ColliderComponent::IsColliding()
{
    return !currentColliders.IsEmpty();
}

// ===============================================================================

void ColliderComponent::OnDestroy()
{
    ColliderManager::Remove(this);

    // these will unsubscribe before everything is deleted
    currentColliders.RemoveAll();
    previousColliders.RemoveAll();
}