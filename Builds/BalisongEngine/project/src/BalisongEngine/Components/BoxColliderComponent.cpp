#include "BoxColliderComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
using namespace BalisongEngine;
using namespace BalisongEngineOCM;
using namespace BalisongEngineComponents;

#include "CircleColliderComponent.h"

#include "Gizmos.h"
using namespace BalisongEngineFramework;

#include <glm/glm.hpp>
using namespace glm;

#include <iostream>
using namespace std;

// ===============================================================================

BoxColliderComponent::BoxColliderComponent(GameObject* go, const string& comp_name) : ColliderComponent(go, comp_name) {}
BoxColliderComponent::~BoxColliderComponent() {}

// ===============================================================================

vec2 BoxColliderComponent::GetBottomLeft() const
{
	vec2 pos = GetCenter();
	return pos - size * 0.5f;
}
vec2 BoxColliderComponent::GetTopRight() const
{
	vec2 pos = GetCenter();
	return pos + size * 0.5f;
}

// ===============================================================================

bool BoxColliderComponent::IsCollidingWith(ColliderComponent* other)
{
    if (auto* other_box = dynamic_cast<BoxColliderComponent*>(other))
    {
        return IsCollidingWithBox(other_box);
    }
    else if (auto* other_circle = dynamic_cast<CircleColliderComponent*>(other))
    {
        return other_circle->IsCollidingWithBox(this);
    }
    return false;
}

// ===============================================================================

bool BoxColliderComponent::IsCollidingWithBox(BoxColliderComponent* other)
{
    auto this_min = GetBottomLeft();
    auto this_max = GetTopRight();

    auto other_min = other->GetBottomLeft();
    auto other_max = other->GetTopRight();

    // AABB check
    bool intersecting_x = (this_max.x >= other_min.x && this_min.x <= other_max.x);
    bool intersecting_y = (this_max.y >= other_min.y && this_min.y <= other_max.y);

    return intersecting_x && intersecting_y;
}

// ===============================================================================

void BoxColliderComponent::Render()
{
    if (!showGizmos) return;

    Gizmos::color = gizmosColor;
    Gizmos::thickness = gizmosThickness;

    Gizmos::DrawBox(size, GetCenter());
}