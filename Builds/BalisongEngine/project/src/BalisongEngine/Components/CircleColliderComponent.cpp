#include "CircleColliderComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
using namespace BalisongEngine;
using namespace BalisongEngineOCM;
using namespace BalisongEngineComponents;

#include "BoxColliderComponent.h"

#include "Gizmos.h"
using namespace BalisongEngineFramework;

#include <glm/glm.hpp>
using namespace glm;

#include <iostream>
using namespace std;

// ===============================================================================

CircleColliderComponent::CircleColliderComponent(GameObject* go, const string& comp_name) : ColliderComponent(go, comp_name) {}
CircleColliderComponent::~CircleColliderComponent() {}

// ===============================================================================

bool CircleColliderComponent::IsCollidingWith(ColliderComponent* other)
{
    if (auto* other_circle = dynamic_cast<CircleColliderComponent*>(other))
    {
        return IsCollidingWithCircle(other_circle);
    }
    else if (auto* other_box = dynamic_cast<BoxColliderComponent*>(other))
    {
        return IsCollidingWithBox(other_box);
    }
    return false;
}

// ===============================================================================

bool CircleColliderComponent::IsCollidingWithCircle(CircleColliderComponent* other)
{
    if (!other) return false;

    auto this_center = GetCenter();
    auto other_center = other->GetCenter();
    auto distance = glm::distance(this_center, other_center);    

    auto combined_radius = radius + other->radius;

    return distance <= combined_radius;
}

// ===============================================================================

bool CircleColliderComponent::IsCollidingWithBox(BoxColliderComponent* other)
{
    if (!other) return false;

    auto this_center = GetCenter();

    auto other_min = other->GetBottomLeft();
    auto other_max = other->GetTopRight();

    // closest point from circle's center to the edge of the box
    vec2 closest_point =
    {
        clamp(this_center.x, other_min.x, other_max.x),
        clamp(this_center.y, other_min.y, other_max.y)
    };

    float distance = glm::distance(this_center, closest_point);

    return distance <= radius;
}

// ===============================================================================

void CircleColliderComponent::Render()
{
    if (!showGizmos) return;

    Gizmos::color = gizmosColor;
    Gizmos::thickness = gizmosThickness;

    Gizmos::DrawCircle(radius, GetCenter());
}