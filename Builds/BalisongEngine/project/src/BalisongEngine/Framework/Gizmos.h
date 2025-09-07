#pragma once
#include <glm/glm.hpp>

namespace BalisongEngine {
namespace BalisongEngineFramework
{
	/// <summary>
	/// The static class to draw lines and shapes for debugging
	/// </summary>
	class Gizmos
	{
	public:

		/// <summary>
		/// The color of the gizmo
		/// </summary>
		static glm::vec4 color;
		/// <summary>
		/// The thickness of the lines
		/// </summary>
		static float thickness;

		/// <summary>
		/// Creates a quad mesh to render
		/// </summary>
		/// <param name="size"></param>
		/// <param name="center"></param>
		/// <param name="rotation"></param>
		/// <param name="scale"></param>
		static void DrawQuad(const glm::vec2& size, const glm::vec2& center, float rotation = 0, const glm::vec2& scale = { 1,1 });

		/// <summary>
		/// Creates a line using the quad mesh to render
		/// </summary>
		/// <param name="from"></param>
		/// <param name="to"></param>
		static void DrawLine(const glm::vec2& from, const glm::vec2& to);
		/// <summary>
		/// Creates a box using 4 quad meshes to render
		/// </summary>
		/// <param name="size"></param>
		/// <param name="center"></param>
		static void DrawBox(const glm::vec2& size, const glm::vec2& center);
		/// <summary>
		/// Creates segments of lines to form a circle to render
		/// </summary>
		/// <param name="radius"></param>
		/// <param name="center"></param>
		/// <param name="segments"></param>
		static void DrawCircle(float radius, const glm::vec2& center, int segments = 36);
	};

}
}
