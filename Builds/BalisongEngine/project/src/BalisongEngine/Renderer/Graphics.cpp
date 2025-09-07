#include "Graphics.h"
using namespace BalisongEngine;

#include "Renderer.h"
#include "Mesh.h"
#include "Texture2D.h"
using namespace BalisongEngineRenderer;

// ====================================================================

void Graphics::DrawMesh(Mesh* mesh, RenderParams params)
{
	DrawCommand dc {};

	dc.meshID = mesh->GetID();
	dc.vertexStride = sizeof(Vertex);
	dc.vertexCount = mesh->GetVertexCount();
	dc.tint = params.tint;
	dc.translation = params.translation;
	dc.rotationZ = params.rotationZ;
	dc.scale = params.scale;

	// Use the texture from params instead of the mesh ID
	// if no texture, set to 0 or a default texture ID if necessary
	dc.textureID = params.texture ? params.texture->GetID() : 0;

	Renderer::SubmitDrawCommand(dc);
}