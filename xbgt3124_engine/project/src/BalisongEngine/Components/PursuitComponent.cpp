#include "PursuitComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
using namespace BalisongEngine;
using namespace BalisongEngineOCM;
using namespace BalisongEngineComponents;

#include "VelocityMeterComponent.h"
#include "MoveComponent.h"

#include <glm/glm.hpp>
using namespace glm;

#include <iostream>
using namespace std;

// ===============================================================================

PursuitComponent::PursuitComponent(GameObject* go, const string& comp_name) : BaseComponent(go, comp_name)
{
    gameObject->EnforceComponent(velocityMeter);
}
PursuitComponent::~PursuitComponent() {}

// ===============================================================================

void PursuitComponent::Update(float dt)
{
	if (!vehicle)
    {
        cerr << bothNames << ": Assign vehicle first!\n";
        return;
    };

    auto target = targetRef.Get();
    if (!target) return;

    if (faceTarget)
    {
        auto target_tr = target->GetTransform();
        auto target_pos = target_tr->GetWorldPosition();
        //vec2 target_pos = predict ? GetPredictedPos() : target->GetWorldPosition();

        transform->LookAt(target_pos, angleOffset);
    }

	auto velocity = GetVelocity();

    auto speed = length(velocity);
	vehicle->SetSpeed(speed);

    if (speed <= 0) return; // normalizing a 0 is buggy af

    auto dir = normalize(velocity);
	vehicle->SetDirection(dir);
}

// ===============================================================================

void PursuitComponent::SetTarget(GameObject* to)
{
    targetRef.Set(to);
    velocityMeter->SetTarget(to);
}

GameObjectRef PursuitComponent::GetTargetRef() const
{
    return targetRef;
}

// ===============================================================================

vec3 PursuitComponent::GetPredictedPos() const
{
    auto target = targetRef.Get();
    auto target_tr = target->GetTransform();
    auto target_pos = target_tr->GetWorldPosition();

    if (!predict) return { target_pos,0 };

    auto distance = transform->GetDistance(target_pos);

    float time_to_reach = distance / maxSpeed;

    auto future_pos = target_pos + (velocityMeter->GetVelocity() * time_to_reach);
    return { future_pos, 0 };
}

// ===============================================================================

vec3 PursuitComponent::GetPredictedDir() const
{
    bool is_facing = IsFacingEachOther();

    bool do_prediction =
        (!evade && !is_facing) ||
        (evade && is_facing);

    auto target = targetRef.Get();
    auto target_tr = target->GetTransform();
    auto target_pos = target_tr->GetWorldPosition();
    vec3 future_pos = do_prediction ? GetPredictedPos() : vec3(target_pos, 0);

    vec3 predicted_dir = { transform->GetDirection(future_pos),0 };
    if (evade) predicted_dir = -predicted_dir;
    return predicted_dir;
}

// ===============================================================================

bool PursuitComponent::IsFacingEachOther() const
{
    auto target = targetRef.Get();
    auto target_tr = target->GetTransform();
    auto target_pos = target_tr->GetWorldPosition();
    vec3 dir_to_target = { transform->GetDirection(target_pos), 0 };
    if (evade) dir_to_target = -dir_to_target;

    vec3 targets_dir = { velocityMeter->GetDirection(), 0 };

    float dot = glm::dot(dir_to_target, targets_dir);
    return dot <= -0.9239f;
}

// ===============================================================================

vec3 PursuitComponent::GetVelocity()
{
    auto target = targetRef.Get();   
    auto target_tr = target->GetTransform();
    auto target_pos = target_tr->GetWorldPosition();
    float distance = transform->GetDistance(target_pos);

    TryMaintainDistance(distance);

    float speed = evade ? GetDepartureSpeed(distance) : GetArrivalSpeed(distance);

    vec3 predicted_dir = GetPredictedDir();

    return speed * predicted_dir;
}

// ===============================================================================

float PursuitComponent::GetArrivalSpeed(float distance)
{    
    if (!arrival) return maxSpeed;

    if (distance <= arrivalRange) return 0;

    if (arrivalSlowingRangeOffset == 0)
    {
        constexpr float epsilon = numeric_limits<float>::epsilon();
        arrivalSlowingRangeOffset = epsilon;
    }

    float ramped_speed = maxSpeed * (distance - arrivalRange) / arrivalSlowingRangeOffset;

    float clipped_speed = glm::min(ramped_speed, maxSpeed);
    return clipped_speed;
}


float PursuitComponent::GetDepartureSpeed(float distance)
{
    if (!departure) return maxSpeed;

    if (distance > departureRange) return 0;

    if (distance <= departureRange - departureSlowingRangeOffset)
        return maxSpeed;

    if (departureSlowingRangeOffset == 0)
    {
        constexpr float epsilon = numeric_limits<float>::epsilon();
        departureSlowingRangeOffset = epsilon;
    }

    float ramped_speed = maxSpeed * (departureRange - distance) / departureSlowingRangeOffset;

    float clipped_speed = glm::min(ramped_speed, maxSpeed);
    return clipped_speed;
}

// ===============================================================================

void PursuitComponent::TryMaintainDistance(float distance)
{
    if (!maintainDistance) return;

    float maintain_range = arrivalRange - maintainRangeOffset;
    maintain_range = glm::max(0.0f, maintain_range);

    bool is_too_close = distance < maintain_range;
    evade = is_too_close;
}

// ===============================================================================

void PursuitComponent::OnDestroy()
{
    SetTarget(nullptr);
}