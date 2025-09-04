#pragma once
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>

// ===============================================================================

namespace BalisongEngine{
namespace BalisongEngineRenderer
{
	/// <summary>
	/// Stores configuration data for a camera, like projection, view, and position
	/// </summary>
	struct CameraConfig
	{
		/// <summary>
		/// Projection matrix of the camera
		/// </summary>
		glm::mat4 projection = glm::mat4(1.0f);
		/// <summary>
		/// Aspect ratio of the camera, width over height
		/// </summary>
		float aspectRatio = 1.0f;
		/// <summary>
		/// Orthographic size of the camera, used for orthographic projections
		/// </summary>
		float orthoSize = 1;
		/// <summary>
		/// View matrix of the camera, its orientation and position
		/// </summary>
		glm::mat4 view = glm::mat4(1.0f);
		/// <summary>
		/// Combined view-projection matrix of the camera
		/// </summary>
		glm::mat4 vp = glm::mat4(1.0f);
		/// <summary>
		/// Position of the camera in world space
		/// </summary>
		glm::vec3 position = glm::vec3(0);
		/// <summary>
		/// If the camera should be recalculated
		/// </summary>
		bool isDirty = true;
	};

	// ====================================================================

	/// <summary>
	/// List of corners of the camera's view
	/// </summary>
	enum class CameraCorner
	{
		TOP_LEFT,
		TOP_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_RIGHT,
	};

	/// <summary>
	/// List of edges of the camera's view
	/// </summary>
	enum class CameraEdge
	{
		TOP,
		BOTTOM,
		LEFT,
		RIGHT,
	};

	// ====================================================================

	/// <summary>
	/// The camera in the scene, using projection and view transformations
	/// </summary>
	class Camera
	{
	public:

		/// <summary>
		/// ctor not for static class
		/// </summary>
		Camera() = delete;

		// ====================================================================

		/// <summary>
		/// Initializes the camera with a configuration and screen dimensions, and recalculates matrices
		/// </summary>
		/// <param name="cfg">CameraConfig</param>
		/// <param name="width">Width</param>
		/// <param name="height">Height</param>
		static void Init(CameraConfig cfg, int width, int height);

		/// <summary>
		/// Updates the aspect ratio, projection matrix, and marks the camera as dirty
		/// </summary>
		/// <param name="width">Width</param>
		/// <param name="height">Height</param>
		static void Recalculate(int width, int height);

		// ====================================================================

		/// <summary>
		/// Gets the projection matrix
		/// </summary>
		/// <returns>mat4 projection</returns>
		static glm::mat4 GetMatrixProjection();
		/// <summary>
		/// Gets the aspect ratio
		/// </summary>
		/// <returns>float aspectRatio</returns>
		static float GetAspectRatio();
		/// <summary>
		/// Gets the orthographic Size
		/// </summary>
		/// <returns>float orthoSize</returns>
		static float GetOrthoSize();

		/// <summary>
		/// Sets new projection matrix and recalculates
		/// </summary>
		/// <param name="to">New value</param>
		void SetMatrixProjection(glm::mat4 to);
		/// <summary>
		/// Sets new aspect ratio and recalculates
		/// </summary>
		/// <param name="to">New value</param>
		void SetAspectRatio(float to);
		/// <summary>
		/// Sets new orthographic size and recalculates
		/// </summary>
		/// <param name="to">New value</param>
		void SetOrthoSize(float to);

		// ====================================================================

		// Virtual Camera

		/// <summary>
		/// Gets the view matrix if the camera is dirty
		/// </summary>
		/// <returns>mat4 view matrix</returns>
		static glm::mat4 GetMatrixView();
		/// <summary>
		/// Gets the view-projection matrix if the camera is dirty
		/// </summary>
		/// <returns>mat4 projection</returns>
		static glm::mat4 GetMatrixViewProjection();

		// ====================================================================

		/// <summary>
		/// Adds to the camera position and marks it as dirty
		/// </summary>
		/// <param name="by">Offset</param>
		static void Translate(glm::vec3 by);
		/// <summary>
		/// Adds to the camera position and marks it as dirty
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="z"></param>
		static void Translate(float x, float y, float z);

		/// <summary>
		/// Sets the camera position and marks it as dirty
		/// </summary>
		/// <param name="to">New position</param>
		static void SetPosition(glm::vec3 to);
		/// <summary>
		/// Sets the camera position and marks it as dirty
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="z"></param>
		static void SetPosition(float x, float y, float z);

		/// <summary>
		/// Gets the camera position in world space
		/// </summary>
		/// <returns></returns>
		static glm::vec2 GetPosition();

		/// <summary>
		/// Converts screen coordinates to world coordinates using the inverse of the view-projection matrix
		/// </summary>
		/// <param name="screen_pos">Screen coordinates</param>
		/// <returns>vec3 World coordinates</returns>
		static glm::vec3 ScreenToWorld(glm::vec2 screen_pos);

		// ====================================================================
		
		/// <summary>
		/// Gets the world position of a corner of the camera view
		/// </summary>
		/// <param name="corner"></param>
		/// <returns></returns>
		static glm::vec2 GetCorner(CameraCorner corner);
		/// <summary>
		/// Gets a random world position along an edge of the camera view
		/// </summary>
		/// <param name="edge"></param>
		/// <param name="expand_offset"></param>
		/// <returns></returns>
		static glm::vec2 GetRandomEdge(CameraEdge edge, float expand_offset=0);
		/// <summary>
		/// Gets a random world position along the borders of the camera view
		/// </summary>
		/// <param name="expand_offset"></param>
		/// <returns></returns>
		static glm::vec2 GetRandomBounds(float expand_offset=0);

		// ====================================================================

	private:

		static int width;
		static int height;

		// ====================================================================

		static glm::mat4 projection;
		static float aspectRatio;
		static float orthoSize;

		// ====================================================================

		static CameraConfig config;

		// ====================================================================

		// Virtual Camera
		static glm::mat4 view;
		static glm::mat4 vp;
		static glm::vec3 position;
		static bool isDirty;

	};

}
}