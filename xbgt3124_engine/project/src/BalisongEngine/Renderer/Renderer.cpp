#include "Renderer.h"
using namespace BalisongEngine;

#include "Camera.h"
using namespace BalisongEngineRenderer;

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <algorithm>
#include <iostream>
using namespace std;

// ===============================================================================

vector<DrawCommand> Renderer::draws;
bool Renderer::isRendering;
glm::mat4 Renderer::vpMatrix;

// ===============================================================================

void Renderer::Init()
{
	glEnable(GL_TEXTURE_2D); // Enable texturing

	glEnable(GL_BLEND); // Enable blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Standard alpha blending

	glEnable(GL_DEPTH_TEST); // Enable depth testing
	glDepthFunc(GL_LEQUAL); // Less than or equal depth function
}

int Renderer::Load()
{
	// init glad
	// if glad init is successful, return 1. Otherwise return 0.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return 0;
	}
	return 1;
}

// ===============================================================================

void Renderer::SetViewport(int x, int y, int width, int height)
{
	if (width == 0 || height == 0) return;
	glViewport(x, y, width, height);

	Camera::Recalculate(width, height);
}

void Renderer::SetClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void Renderer::ClearFramebuffer()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

// ===============================================================================

void Renderer::SubmitDrawCommand(DrawCommand dc)
{
	if (!isRendering)
	{
		cout << "Rendering commands only submittable in render step!" << endl;
		return;
	}
	// add dc to draws.
	draws.push_back(dc);
}

// ===============================================================================

void Renderer::BeginFrame()
{
	isRendering = true;

	// Clear the renderer
	ClearFramebuffer();

	// Set the vp (view-projection) matrix
	//Renderer::vpMatrix = Camera::getMatrix_projection();
	Renderer::vpMatrix = Camera::GetMatrixViewProjection();
}

void Renderer::EndFrame()
{
	// Set common settings
	glPushMatrix(); // Push matrix to stack.
	glLoadMatrixf(&vpMatrix[0][0]); // Load view-projection matrix.
	glEnableClientState(GL_VERTEX_ARRAY); // Enable vertex array state.
	glEnableClientState(GL_TEXTURE_COORD_ARRAY); // Enable texcoord array state.

	// Sort transparent objects from back-to-front
	sort(draws.begin(), draws.end(), [](const DrawCommand& a, const DrawCommand& b)
	{
		return a.translation.z > b.translation.z;
	});

	glDepthMask(GL_FALSE); // Disable z write because all objects are transparent

	for (const auto& dc : draws) // Render them
	{
		RenderDrawCommand(dc);
	}

	glDepthMask(GL_TRUE);
	
	// Remember to unbind texture after drawing all requests.
	glBindTexture(GL_TEXTURE_2D, 0);

	// Unset common settings
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind any bounded VBO
	glDisableClientState(GL_VERTEX_ARRAY); // Disable vertex array state.
	glDisableClientState(GL_TEXTURE_COORD_ARRAY); // Disable texcoord array state.
	glPopMatrix(); // Pop matrix from stack.

	// Clear draws and set isRendering to false
	draws.clear();
	isRendering = false;
}

// ===============================================================================

void Renderer::RenderDrawCommand(const DrawCommand& dc)
{
	glPushMatrix();

	// Apply Transformation
	glTranslatef(dc.translation.x, dc.translation.y, dc.translation.z);
	glRotatef(dc.rotationZ, 0, 0, 1); // z-axis only
	glScalef(dc.scale.x, dc.scale.y, dc.scale.z);

	// Apply materials
	glColor4fv(&dc.tint[0]);

	// The texture needs to be bound before drawing.
	// Note: Texture feature already enabled by default in Renderer::init()
	glBindTexture(GL_TEXTURE_2D, dc.textureID);

	// Draw Object
	glBindBuffer(GL_ARRAY_BUFFER, dc.meshID);
	glVertexPointer(3, GL_FLOAT, dc.vertexStride, 0);
	glTexCoordPointer(2, GL_FLOAT, dc.vertexStride, (void*)12);
	glDrawArrays(GL_TRIANGLES, 0, dc.vertexCount);

	glPopMatrix();
}
