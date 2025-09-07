#pragma once
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <vector>

// ===============================================================================

namespace BalisongEngine{
namespace BalisongEngineRenderer
{
	/// <summary>
	/// A command to draw a specific object with preset properties
	/// </summary>
	struct DrawCommand
	{
		/// <summary>
		/// The ID of the mesh to render
		/// </summary>
		int meshID;
		/// <summary>
		/// The stride of the vertices in the mesh
		/// </summary>
		int vertexStride;
		/// <summary>
		/// The number of vertices to draw
		/// </summary>
		int vertexCount;

		/// <summary>
		/// The color tint for the mesh being rendered
		/// </summary>
		glm::vec4 tint;
		/// <summary>
		/// The position of the object in world space
		/// </summary>
		glm::vec3 translation;
		/// <summary>
		/// The rotation on the z axis
		/// </summary>
		float rotationZ;
		/// <summary>
		/// The scale of the mesh
		/// </summary>
		glm::vec3 scale;

		/// <summary>
		/// The ID of the texture to use for rendering
		/// </summary>
		unsigned int textureID;
	};

	// ===============================================================================

	/// <summary>
	/// The static class for rendering objects using the preset draw commands
	/// </summary>
	class Renderer
	{
	private:

		/// <summary>
		/// ctor not for static class
		/// </summary>
		Renderer() = delete;

		// ===============================================================================

		static bool isRendering;
		static glm::mat4 vpMatrix;

		// ===============================================================================

		static std::vector<DrawCommand> draws;
		static void RenderDrawCommand(const DrawCommand& dc);

		// ===============================================================================

	public:

		/// <summary>
		/// Initializes OpenGL features for rendering, and checks if OpenGL is prepared for rendering
		/// </summary>
		static void Init();
		/// <summary>
		/// Initializes the GLAD loader to link OpenGL functions
		/// </summary>
		/// <returns>1 on success and 0 on failure</returns>
		static int Load();

		// ===============================================================================

		/// <summary>
		/// Sets the OpenGL viewport dimensions and position. Recalculates the camera to match
		/// </summary>
		/// <param name="x">Position X</param>
		/// <param name="y">Position Y</param>
		/// <param name="width">Width</param>
		/// <param name="height">Height</param>
		static void SetViewport(int x, int y, int width, int height);
		/// <summary>
		/// Sets the background color (OpenGL clear color for rendering)
		/// </summary>
		/// <param name="r">Red</param>
		/// <param name="g">Green</param>
		/// <param name="b">Blue</param>
		/// <param name="a">Alpha</param>
		static void SetClearColor(float r, float g, float b, float a);
		/// <summary>
		/// Clears the framebuffer's depth and color buffers for preparing the screen before rendering each frame
		/// </summary>
		static void ClearFramebuffer();

		// ===============================================================================

		/// <summary>
		/// Queues a DrawCommand for rendering
		/// </summary>
		/// <param name="dc">DrawCommand</param>
		static void SubmitDrawCommand(DrawCommand dc);

		// ===============================================================================

		/// <summary>
		/// Clears the framebuffer and sets the view-projection matrix for rendering
		/// </summary>
		static void BeginFrame();
		/// <summary>
		/// Executes all queued DrawCommand objects. Unbinds textures, disables client states, and clears the render queue
		/// </summary>
		static void EndFrame();

	};

}
}
