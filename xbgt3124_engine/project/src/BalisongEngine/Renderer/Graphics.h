#pragma once
#include <glm\glm.hpp>

// ===============================================================================

namespace BalisongEngine{
namespace BalisongEngineRenderer
{
	class Texture2D; // forward declare
	class Mesh; // forward declare

	// ====================================================================

	/// <summary>
	/// A simple material data for a mesh
	/// </summary>
	struct RenderParams
	{
		/// <summary>
		/// The red, green, blue, and alpha values of a mesh
		/// </summary>
		glm::vec4 tint;

		/// <summary>
		/// The positioning of a mesh
		/// </summary>
		glm::vec3 translation;
		/// <summary>
		/// The rotation in the z axis of a mesh
		/// </summary>
		float rotationZ;
		/// <summary>
		/// The scale of a mesh
		/// </summary>
		glm::vec3 scale;

		/// <summary>
		/// The texture of a mesh
		/// </summary>
		Texture2D* texture;
	};

	// ====================================================================

	/// <summary>
	/// The static class to draw meshes
	/// </summary>
	class Graphics
	{
	public:

		/// <summary>
		/// ctor not for static class
		/// </summary>
		Graphics() = delete;

		/// <summary>
		/// Renders a mesh using a preset
		/// </summary>
		/// <param name="mesh"></param>
		/// <param name="params"></param>
		static void DrawMesh(Mesh* mesh, RenderParams params);
	};

}
}