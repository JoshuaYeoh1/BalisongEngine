#pragma once
#include <glm/glm.hpp>
#include <vector>

// ===============================================================================

namespace BalisongEngine{
namespace BalisongEngineRenderer
{
	/// <summary>
	/// Contains the position and UV values
	/// </summary>
	struct Vertex
	{
		/// <summary>
		/// The position of vertex
		/// </summary>
		float x, y, z;
		/// <summary>
		/// The UV values of vertex
		/// </summary>
		float u, v;

		/// <summary>
		/// ctor
		/// </summary>
		Vertex() : x(0), y(0), z(0), u(0), v(0) {}
		/// <summary>
		/// ctor
		/// </summary>
		/// <param name="pos"></param>
		/// <param name="uv"></param>
		Vertex(glm::vec3 pos, glm::vec2 uv) : x(pos.x), y(pos.y), z(pos.z), u(uv.x), v(uv.y) {}
	};

	// ====================================================================
	
	/// <summary>
	/// For creating meshes with vertices and an ID
	/// </summary>
	class Mesh
	{

	public:

		/// <summary>
		/// ctor
		/// </summary>
		/// <param name="vertices"></param>
		Mesh(std::vector<Vertex> vertices);
		~Mesh();

		// ====================================================================
		
		/// <summary>
		/// Change the vertices of the existing mesh
		/// </summary>
		/// <param name="vertices"></param>
		void UpdateVertices(std::vector<Vertex> vertices);
		
		// ====================================================================

		/// <summary>
		/// Gets the mesh ID
		/// </summary>
		/// <returns></returns>
		unsigned int GetID();
		/// <summary>
		/// Gets the number of vertices in the mesh
		/// </summary>
		/// <returns></returns>
		int GetVertexCount();

		// ====================================================================

	private:

		unsigned int id = 0;
		int vertexCount = 0;
	};

}
}