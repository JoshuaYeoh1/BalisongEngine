#include "TransformComponent.h"
#include "GameObject.h"
using namespace BalisongEngine;
using namespace BalisongEngineOCM;
using namespace BalisongEngineComponents;

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <iostream>
using namespace std;

// ===============================================================================

TransformComponent::TransformComponent(GameObject* go, const string& comp_name) : BaseComponent(go, comp_name), parent(nullptr) {}
TransformComponent::~TransformComponent() {}

// ===============================================================================

vec2 TransformComponent::GetLocalPosition() const
{
	return localPosition;
}

void TransformComponent::SetLocalPosition(vec2 to)
{
	localPosition = to;
}
void TransformComponent::SetLocalPosition(float x, float y)
{
	localPosition = vec2(x, y);
}

void TransformComponent::TranslateLocal(vec2 by)
{
	localPosition += by;
}
void TransformComponent::TranslateLocal(float x, float y)
{
	localPosition += vec2(x, y);
}

// ===============================================================================
	
vec2 TransformComponent::GetWorldPosition() const
{
	return vec2(GetModelMatrix()[3]);
}

void TransformComponent::SetWorldPosition(vec2 to)
{
	if (!parent)
	{
		localPosition = to;
		return;
	}

	// local position relative to parent
	mat4 parent_matrix = parent->GetModelMatrix();
	vec3 local_pos = inverse(parent_matrix) * vec4(to, 0, 1);

	localPosition = vec2(local_pos);
}
void TransformComponent::SetWorldPosition(float x, float y)
{
	SetWorldPosition(vec2(x, y));
}

// ===============================================================================

float TransformComponent::GetLocalRotation() const
{
	return localRotation;
}

void TransformComponent::SetLocalRotation(float angle)
{
	localRotation = angle;
}

void TransformComponent::RotateLocal(float by)
{
	localRotation += by;
}

// ===============================================================================

float TransformComponent::GetWorldRotation() const
{
	mat3 rotation_matrix = mat3(GetModelMatrix());
	return degrees(atan2(rotation_matrix[1][0], rotation_matrix[0][0]));
}

void TransformComponent::SetWorldRotation(float angle)
{
	if (!parent)
	{
		localRotation = angle;
		return;
	}

	// local rotation relative to parent
	float parent_rotation = parent->GetWorldRotation();
	localRotation = angle - parent_rotation;
}

// ===============================================================================

vec2 TransformComponent::GetLocalScale() const
{
	return localScale;
}

void TransformComponent::SetLocalScale(vec2 to)
{
	localScale = to;
}
void TransformComponent::SetLocalScale(float x, float y)
{
	localScale = vec2(x, y);
}
void TransformComponent::SetLocalScale(float to)
{
	localScale = vec2(to);
}

void TransformComponent::AddLocalScale(vec2 by)
{
	localScale += by;
}
void TransformComponent::AddLocalScale(float x, float y)
{
	localScale += vec2(x, y);
}
void TransformComponent::AddLocalScale(float by)
{
	localScale += vec2(by);
}

void TransformComponent::LocalScaleMult(vec2 by)
{
	localScale *= by;
}
void TransformComponent::LocalScaleMult(float x, float y)
{
	LocalScaleMult({ x,y });
}
void TransformComponent::LocalScaleMult(float by)
{
	LocalScaleMult({ by,by });
}

// ===============================================================================

vec2 TransformComponent::GetWorldScale() const
{
	// Remove translation and rotation
	mat3 rotation_matrix = mat3(GetModelMatrix());

	vec3 scale =
		vec3(length(rotation_matrix[0]), // X scale
			 length(rotation_matrix[1]), // Y scale
			 length(rotation_matrix[2])); // Z scale

	return vec2(scale);
}

void TransformComponent::SetWorldScale(vec2 to)
{
	if (!parent)
	{
		localScale = to;
		return;
	}

	// local scale relative to parent's scale
	vec2 parent_scale = parent->GetWorldScale();
	localScale = to / parent_scale;
}
void TransformComponent::SetWorldScale(float x, float y)
{
	SetWorldScale(vec2(x, y));
}
void TransformComponent::SetWorldScale(float to)
{
	SetWorldScale(vec2(to));
}

// ===============================================================================

mat4 TransformComponent::GetModelMatrix() const
{
	// Translate last
	// Rotation second; Make quaternion with rotation in radians, and then convert to mat4
	// Scale first
	mat4 model_matrix =
		translate(mat4(1), vec3(localPosition, 0)) *
		toMat4(quat( vec3(0, 0, radians(localRotation)) )) *
		scale(mat4(1), vec3(localScale, 1));

	if (parent)
	{
		return parent->GetModelMatrix() * model_matrix;
	}
	return model_matrix;
}

TransformComponent* TransformComponent::GetParent() const
{
	return parent;
}
void TransformComponent::SetParent(TransformComponent* target)
{
	if (parent == target) return;

	if (parent) parent->RemoveChild(this);

	if (target) target->AddChild(this);
	
	parent = target;
}

void TransformComponent::AddChild(TransformComponent* child)
{
	// no duplicates
	if (find(children.begin(), children.end(), child) == children.end())
	{
		children.push_back(child);
		child->parent = this;
	}
}
void TransformComponent::RemoveChild(TransformComponent* child)
{
	auto it = find(children.begin(), children.end(), child);

	if (it != children.end())
	{
		children.erase(it);
		if(child) child->parent = nullptr;
	}
}
void TransformComponent::DeleteChildren()
{
	if (children.size() == 0) return;

	for (auto* child : children)
	{
		if (child && child->gameObject)
		{
			child->SetParent(nullptr);
			child->gameObject->Destroy();
		}
	}
	children.clear();
}

// ===============================================================================

vec2 TransformComponent::GetLocalUp() const
{
	mat4 model_matrix = GetModelMatrix();
	return normalize(vec3(model_matrix[1]));
}

vec2 TransformComponent::GetLocalDown() const
{
	return -GetLocalUp();
}

vec2 TransformComponent::GetLocalRight() const
{
	mat4 model_matrix = GetModelMatrix();
	return normalize(vec3(model_matrix[0]));
}

vec2 TransformComponent::GetLocalLeft() const
{
	return -GetLocalRight();
}

// ===============================================================================

vec2 TransformComponent::GetDirection(vec2 to) const
{
	auto vector = to - GetWorldPosition();

	if (length(vector) == 0) return { 0,1 }; // default as up

	return normalize(vector); // normalizing a 0 is buggy af
}

void TransformComponent::FaceDirection(vec2 to, float angle_offset)
{
	float radians = atan2(to.y, to.x);
	constexpr auto pie = pi<float>();
	float degrees = radians * (180 / pie);
	SetWorldRotation(degrees + angle_offset - 90); // facing up by default
}

void TransformComponent::LookAt(vec2 pos, float angle_offset)
{
	auto dir = GetDirection(pos);
	FaceDirection(dir, angle_offset);
}

// ===============================================================================

float TransformComponent::GetDistance(vec2 to) const
{
	auto vector = to - GetWorldPosition();
	return length(vector);
}

// ===============================================================================

vec2 TransformComponent::TransformPoint(vec2 pos) const
{
	mat4 model_matrix = GetModelMatrix();
	vec4 local_pos(pos, 0, 1); // set w to 1 for points
	vec4 world_pos = model_matrix * local_pos; // apply position, rotation, scale

	return vec2(world_pos.x, world_pos.y);
}

vec2 TransformComponent::TransformDirection(vec2 dir) const
{
	mat4 model_matrix = GetModelMatrix();
	mat3 rotation_matrix = mat3(model_matrix); // get only the rotation part from the model matrix
	vec3 local_dir(dir, 0);
	vec3 world_dir = rotation_matrix * local_dir; // apply rotation

	return vec2(world_dir.x, world_dir.y);
}

// ===============================================================================

void TransformComponent::OnDestroyComponent()
{
	if (parent) parent->RemoveChild(this);

	DeleteChildren();
}