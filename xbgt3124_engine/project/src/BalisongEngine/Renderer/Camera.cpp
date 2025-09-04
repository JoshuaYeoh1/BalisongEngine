#include "Camera.h"
using namespace BalisongEngine;
using namespace BalisongEngineRenderer;

#include "Random.h"
using namespace BalisongEngineFramework;

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

// ====================================================================

// Define the static Camera variables, by default:

// projection is identity matrix, aspect ratio is 1.0f
mat4 Camera::projection = mat4(1.0f);  
float Camera::aspectRatio = 1.0f;                
float Camera::orthoSize = 1.0f;					

// and config has the default value.
CameraConfig Camera::config = CameraConfig();

// ====================================================================

void Camera::Init(CameraConfig cfg, int width, int height)
{
	Camera::config = cfg;
	Camera::width = width;
	Camera::height = height;
	Recalculate(width, height);
}

void Camera::Recalculate(int width, int height)
{
	Camera::width = width;
	Camera::height = height;

	aspectRatio = width / (float)height;

	// minX and minY is -maxX and -maxY respectively.
	float maxY = orthoSize;
	float maxX = maxY * aspectRatio;
	float minZ = -99999;
	float maxZ = 99999;

	projection = ortho(-maxX, maxX, -maxY, maxY, minZ, maxZ);

	isDirty = true;
}

// ====================================================================

mat4 Camera::GetMatrixProjection()
{
	return projection;
}
float Camera::GetAspectRatio()
{
	return aspectRatio;
}
float Camera::GetOrthoSize()
{
	return orthoSize;
}

// ====================================================================

// store values
int Camera::width = 600;
int Camera::height = 600;

void Camera::SetMatrixProjection(mat4 to)
{
	projection = to;
	Recalculate(width, height);
}
void Camera::SetAspectRatio(float to)
{
	aspectRatio = to;
	Recalculate(width, height);
}
void Camera::SetOrthoSize(float to)
{
	orthoSize = to;
	Recalculate(width, height);
}

// ====================================================================

// Virtual Camera

// view is identity matrix
// vp is identity matrix
// position is zero vector
// isDirty is true
mat4 Camera::view = mat4(1.0f);
mat4 Camera::vp = mat4(1.0f);
vec3 Camera::position = vec3(0);
bool Camera::isDirty = true;

// ====================================================================

mat4 Camera::GetMatrixView()
{
	if (isDirty)
	{
		isDirty = false;

		// recalculate view matrix
		// inverse of the camera's transform
		view = translate(mat4(1.0f), -position);

		// recalculate view-projection (vp) matrix
		vp = projection * view;
	}
	// return view matrix
	return view;
}

mat4 Camera::GetMatrixViewProjection()
{
	// this already has the isDirty checking
	// recalculates view-projection matrix
	GetMatrixView();

	// return view-projection (vp) matrix
	return vp;
}

// ====================================================================

void Camera::Translate(vec3 by)
{
	// Add translation to Camera::position
	Camera::position += by;
	// Set isDirty to true
	isDirty = true;
}

void Camera::Translate(float x, float y, float z)
{
	Translate(vec3(x, y, z));
}

// ====================================================================

void Camera::SetPosition(vec3 position)
{
	// Set position to Camera::position
	Camera::position = position;
	// Set isDirty to true
	isDirty = true;
}

void Camera::SetPosition(float x, float y, float z)
{
	SetPosition(vec3(x, y, z));
}

vec2 Camera::GetPosition()
{
	return Camera::position;
}

// ====================================================================

vec3 Camera::ScreenToWorld(vec2 screen_pos)
{
	// Normalize screenPos to -1~1 range
	float normX = 2.0f * (screen_pos.x / width) - 1.0f;
	float normY = 2.0f * (screen_pos.y / height) - 1.0f;

	// Make a homogeneous vector
	vec4 ndc_pos(normX, normY, 0.0f, 1.0f);

	// Calculation is by multiplying the homogenous vector
	// with the inverse of view-projection
	mat4 vp_inversed = inverse(vp);
	vec4 world_pos = vp_inversed * ndc_pos;

	// return the x,y,0 coordinate which is in the world space.
	return vec3(world_pos.x, world_pos.y, 0.0f);
}

// ====================================================================

vec2 Camera::GetCorner(CameraCorner corner)
{
	vec2 corner_pos = { 0,0 };

	// camera's view frustum in in local space (camera space)
	switch (corner)
	{
	case CameraCorner::TOP_LEFT:
		corner_pos = { -orthoSize * aspectRatio, orthoSize }; break;
	
	case CameraCorner::TOP_RIGHT:
		corner_pos = { orthoSize * aspectRatio, orthoSize }; break;

	case CameraCorner::BOTTOM_LEFT:
		corner_pos = { -orthoSize * aspectRatio, -orthoSize }; break;

	case CameraCorner::BOTTOM_RIGHT:
		corner_pos = { orthoSize * aspectRatio, -orthoSize }; break;
	}

	// camera space to world space using the view matrix
	mat4 inv_view = inverse(view);
	vec4 transformed_pos = inv_view * vec4(corner_pos, 0.0f, 1.0f);
	return vec2(transformed_pos.x + position.x, transformed_pos.y + position.y) ;
}

vec2 Camera::GetRandomEdge(CameraEdge edge, float expand_offset)
{
	vec2 pos1 = { 0,0 };
	vec2 pos2 = { 0,0 };
	vec2 pos = { 0,0 };

	switch (edge)
	{
	case CameraEdge::TOP:
	{
		pos1 = GetCorner(CameraCorner::TOP_LEFT);
		pos2 = GetCorner(CameraCorner::TOP_RIGHT);
		pos1.y += expand_offset;
		pos2.y += expand_offset;
	}
	break;
		
	case CameraEdge::BOTTOM:
	{
		pos1 = GetCorner(CameraCorner::BOTTOM_LEFT);
		pos2 = GetCorner(CameraCorner::BOTTOM_RIGHT);
		pos1.y -= expand_offset;
		pos2.y -= expand_offset;
	}
	break;

	case CameraEdge::LEFT:
	{
		pos1 = GetCorner(CameraCorner::TOP_LEFT);
		pos2 = GetCorner(CameraCorner::BOTTOM_LEFT);
		pos1.x -= expand_offset;
		pos2.x -= expand_offset;
	}
	break;

	case CameraEdge::RIGHT:
	{
		pos1 = GetCorner(CameraCorner::TOP_RIGHT);
		pos2 = GetCorner(CameraCorner::BOTTOM_RIGHT);
		pos1.x += expand_offset;
		pos2.x += expand_offset;
	}
	break;
	}

	pos.x = Random::Range(pos1.x, pos2.x);
	pos.y = Random::Range(pos1.y, pos2.y);
	return pos;
}

vec2 Camera::GetRandomBounds(float expand_offset)
{
	CameraEdge edge = CameraEdge::TOP;
	int edge_num = Random::Range(1, 5);

	switch (edge_num)
	{
	case 1: edge = CameraEdge::TOP; break;
	case 2: edge = CameraEdge::BOTTOM; break;
	case 3: edge = CameraEdge::LEFT; break;
	case 4: edge = CameraEdge::RIGHT; break;
	}
	
	return GetRandomEdge(edge, expand_offset);
}

