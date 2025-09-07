#include "SpriteRendererComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
using namespace BalisongEngine;
using namespace BalisongEngineOCM;
using namespace BalisongEngineComponents;

#include "Allocator.h"
using namespace BalisongEngineAllocator;

#include "Random.h"
using namespace BalisongEngineFramework;

#include "Graphics.h"
#include "Mesh.h"
#include "Texture2D.h"
using namespace BalisongEngineRenderer;

#include <glm/glm.hpp>
using namespace glm;

#include <glad/glad.h>

#include <iostream>
using namespace std;

// ===============================================================================

SpriteRendererComponent::SpriteRendererComponent(GameObject* go, const string& comp_name) : BaseComponent(go, comp_name)
{
	CreateOrUpdateQuad();
}

SpriteRendererComponent::~SpriteRendererComponent()
{
	// Release the texture resource through the Allocator
	Allocator::ReturnResource<Texture2D>(texture);
}

// ===============================================================================

void SpriteRendererComponent::CreateOrUpdateQuad()
{
	auto size = GetSize();
	
	vector<Vertex> vertices =
	{
		Vertex({ 0, size.y, 0 }, { 0, 1 }),
		Vertex({ 0, 0, 0 }, { 0, 0 }),
		Vertex({ size.x, 0, 0 }, { 1, 0 }),

		Vertex({ size.x, 0, 0 }, { 1, 0 }),
		Vertex({ size.x, size.y, 0 }, { 1, 1 }),
		Vertex({ 0, size.y, 0 }, { 0, 1 })
	};

	// offset vertices by the pivot and z-index
	for (auto& vertex : vertices)
	{
		vertex.x -= size.x * pivot.x;
		vertex.y -= size.y * pivot.y;
		vertex.z = (float) zIndex;
	}

	if (quad) // update existing
	{
		quad->UpdateVertices(vertices);
	}
	else // create new if doesnt exist yet
	{
		quad = new Mesh(vertices);
	}
}

// ===============================================================================

void SpriteRendererComponent::SetPixelSize(vec2 to)
{
	pixelSize = to;
	CreateOrUpdateQuad();

	cout << bothNames << ": Size set to " << pixelSize.x << "x" << pixelSize.y << endl;
}
void SpriteRendererComponent::SetPixelSize(float width, float height)
{
	SetPixelSize({ width,height });
}
vec2 SpriteRendererComponent::GetPixelSize() const
{
	return pixelSize;
}

// ===============================================================================

void SpriteRendererComponent::SetPixelsPerUnit(int to)
{
	pixelsPerUnit = to;
	CreateOrUpdateQuad();

	cout << bothNames << ": Pixels Per Unit set to " << pixelsPerUnit << endl;
}
int SpriteRendererComponent::GetPixelsPerUnit() const
{
	return pixelsPerUnit;
}

// ===============================================================================

vec2 SpriteRendererComponent::GetSize() const
{
	if (pixelsPerUnit == 0) return { 0,0 };

	return { pixelSize.x / pixelsPerUnit, pixelSize.y / pixelsPerUnit };
}

// ===============================================================================

void SpriteRendererComponent::SetPivot(vec2 to)
{
	pivot = to;
	CreateOrUpdateQuad();
}
void SpriteRendererComponent::SetPivot(float x, float y)
{
	SetPivot({ x,y });
}
vec2 SpriteRendererComponent::GetPivot() const
{
	return pivot;
}

// ===============================================================================

void SpriteRendererComponent::SetZIndex(int to)
{
	zIndex = to;
	CreateOrUpdateQuad();

	cout << bothNames << ": Z-Index set to " << zIndex << endl;
}
int SpriteRendererComponent::GetZIndex() const
{
	return zIndex;
}

// ===============================================================================

void SpriteRendererComponent::Render()
{
	auto pos = transform->GetWorldPosition();
	auto rot = -transform->GetWorldRotation(); // apparently must invert rotation
	auto scale = transform->GetWorldScale();

	// Bind the texture before drawing
	glBindTexture(GL_TEXTURE_2D, texture->GetID());

	RenderParams param{};
	param.tint = tint;
	param.translation = { pos.x, pos.y, 0 };
	param.rotationZ = rot;
	param.scale = { scale.x, scale.y, 1 };
	param.texture = texture;

	Graphics::DrawMesh(quad, param);
}

// ===============================================================================

void SpriteRendererComponent::SetTexture(string texture_path, TextureConfig cfg)
{
	if (currentPath == texture_path) return;
	currentPath = texture_path;

	cfg.useMipmaps = false; // not working

	// must release the current texture resource if there is one
	if (texture)
	{
		Allocator::ReturnResource<Texture2D>(texture);
		texture = nullptr;
	}

	// texture = new Texture2D(texture_path, cfg); // without using allocator
	texture = Allocator::GetResource<Texture2D>(ResourceType::TEXTURE, texture_path); // using allocator

	if (texture)
	{
		texture->SetTextureConfig(cfg);
		SetPixelSize(texture->GetSize());
	}
}

// overload for default cfg
void SpriteRendererComponent::SetTexture(string texture_path)
{
	TextureConfig cfg {};
	cfg.wrapModeX = TextureWrapMode::REPEAT;
	cfg.wrapModeY = TextureWrapMode::REPEAT;
	cfg.filterMode = TextureFilterMode::NEAREST;
	cfg.useMipmaps = false;

	SetTexture(texture_path, cfg);
}

// ===============================================================================

void SpriteRendererComponent::SetTint(vec4 to)
{
	tint = to;
}
vec4 SpriteRendererComponent::GetTint() const
{
	return tint;
}

void SpriteRendererComponent::SetColor(vec3 to)
{
	tint = vec4(to, tint.a);
}
void SpriteRendererComponent::SetColor(float r, float g, float b)
{
	SetColor(vec3(r, g, b));
}
vec3 SpriteRendererComponent::GetColor() const
{
	return vec3(tint);
}

void SpriteRendererComponent::OffsetColor(vec3 by)
{
	tint += vec4(by, 0);
}
void SpriteRendererComponent::OffsetColor(float r, float g, float b)
{
	OffsetColor({ r,g,b });
}
void SpriteRendererComponent::OffsetColor(float by)
{
	OffsetColor({ by,by,by });
}

void SpriteRendererComponent::RandomOffsetColor(vec3 by)
{
	float r = Random::Range(-by.r, by.r);
	float g = Random::Range(-by.g, by.g);
	float b = Random::Range(-by.b, by.b);
	OffsetColor(r, g, b);
}
void SpriteRendererComponent::RandomOffsetColor(float r, float g, float b)
{
	RandomOffsetColor({ r,g,b });
}
void SpriteRendererComponent::RandomOffsetColor(float by)
{
	RandomOffsetColor({ by,by,by });
}

void SpriteRendererComponent::SetOpacity(float to)
{
	tint.a = to;
}
float SpriteRendererComponent::GetOpacity() const
{
	return tint.a;
}

// ===============================================================================

string SpriteRendererComponent::GetCurrentPath() const
{
	return currentPath;
}