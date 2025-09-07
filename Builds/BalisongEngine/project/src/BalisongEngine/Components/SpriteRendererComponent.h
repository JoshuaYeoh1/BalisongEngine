#pragma once
#include "BaseComponent.h"
#include <glm/glm.hpp>

// ===============================================================================

namespace BalisongEngine
{
	namespace BalisongEngineRenderer
	{
		class Mesh; // forward declare
		class Texture2D; // forward declare
		struct TextureConfig; // forward declare
	}

namespace BalisongEngineComponents
{
	/// <summary>
	/// The component to create a quad mesh to display an image or texture file at the GameObject transform
	/// </summary>
	class SpriteRendererComponent : public BaseComponent
	{
	public:

		/// <summary>
		/// ctor
		/// </summary>
		/// <param name="go"></param>
		/// <param name="comp_name"></param>
		SpriteRendererComponent(BalisongEngineOCM::GameObject* go, const std::string& comp_name = "[SpriteRendererComponent]");
		~SpriteRendererComponent();

		// ===============================================================================
		
		/// <summary>
		/// Set the size in pixels
		/// </summary>
		/// <param name="to"></param>
		void SetPixelSize(glm::vec2 to);
		/// <summary>
		/// Set the size in pixels
		/// </summary>
		/// <param name="width"></param>
		/// <param name="height"></param>
		void SetPixelSize(float width, float height);
		/// <summary>
		/// Get the size in pixels
		/// </summary>
		/// <returns></returns>
		glm::vec2 GetPixelSize() const;

		/// <summary>
		/// Set the PPU
		/// </summary>
		/// <param name="to"></param>
		void SetPixelsPerUnit(int to);
		/// <summary>
		/// Get the PPU
		/// </summary>
		/// <returns></returns>
		int GetPixelsPerUnit() const;

		/// <summary>
		/// Get the actual size after pixels divided by PPU
		/// </summary>
		/// <returns></returns>
		glm::vec2 GetSize() const;

		/// <summary>
		/// Set the pivot point
		/// </summary>
		/// <param name="to"></param>
		void SetPivot(glm::vec2 to);
		/// <summary>
		/// Set the pivot point
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		void SetPivot(float x, float y);
		/// <summary>
		/// Get the pivot point
		/// </summary>
		/// <returns></returns>
		glm::vec2 GetPivot() const;

		/// <summary>
		/// Set the z-index/layer in order
		/// </summary>
		/// <param name="to"></param>
		void SetZIndex(int to);
		/// <summary>
		/// Get the z-index/layer in order
		/// </summary>
		/// <returns></returns>
		int GetZIndex() const;

		// ===============================================================================

		void Render() override;

		// ===============================================================================

		/// <summary>
		/// Set the texture on the mesh/quad
		/// </summary>
		/// <param name="texture_path">File path. Always starts with '../assets/'</param>
		/// <param name="cfg">Config for wrap mode, filter mode, and mipmaps</param>
		void SetTexture(std::string texture_path, BalisongEngineRenderer::TextureConfig cfg);
		/// <summary>
		/// Set the texture on the mesh/quad
		/// </summary>
		/// <param name="texture_path"></param>
		void SetTexture(std::string texture_path = "../assets/");
		
		// ===============================================================================

		/// <summary>
		/// Sets the tint color, including alpha/opacity
		/// </summary>
		/// <param name="to"></param>
		void SetTint(glm::vec4 to);
		/// <summary>
		/// Gets the tint color, including alpha/opacity
		/// </summary>
		/// <returns></returns>
		glm::vec4 GetTint() const;

		/// <summary>
		/// Sets the RGB of tint, preserving the alpha
		/// </summary>
		/// <param name="to"></param>
		void SetColor(glm::vec3 to);
		/// <summary>
		/// Sets the RGB of tint, preserving the alpha
		/// </summary>
		/// <param name="r"></param>
		/// <param name="g"></param>
		/// <param name="b"></param>
		void SetColor(float r, float g, float b);
		/// <summary>
		/// Gets the RGB of tint, ignoring the alpha 
		/// </summary>
		/// <param name="to"></param>
		glm::vec3 GetColor() const;

		/// <summary>
		/// Adds to the RGB of tint, preserving the alpha
		/// </summary>
		/// <param name="by"></param>
		void OffsetColor(glm::vec3 by);
		/// <summary>
		/// Adds to the RGB of tint, preserving the alpha
		/// </summary>
		/// <param name="r"></param>
		/// <param name="g"></param>
		/// <param name="b"></param>
		void OffsetColor(float r, float g, float b);
		/// <summary>
		/// Adds to the RGB of tint, preserving the alpha
		/// </summary>
		/// <param name="by"></param>
		void OffsetColor(float by);

		/// <summary>
		/// Adds a random amount to the RGB of tint, preserving the alpha
		/// </summary>
		/// <param name="by"></param>
		void RandomOffsetColor(glm::vec3 by);
		/// <summary>
		/// Adds a random amount to the RGB of tint, preserving the alpha
		/// </summary>
		/// <param name="r"></param>
		/// <param name="g"></param>
		/// <param name="b"></param>
		void RandomOffsetColor(float r, float g, float b);
		/// <summary>
		/// Adds a random amount to the RGB of tint, preserving the alpha
		/// </summary>
		/// <param name="by"></param>
		void RandomOffsetColor(float by);

		/// <summary>
		/// Sets the alpha of tint, preserving the RGB
		/// </summary>
		/// <param name="to"></param>
		void SetOpacity(float to);
		/// <summary>
		/// Gets the alpha of tint, ignoring the RGB
		/// </summary>
		/// <returns></returns>
		float GetOpacity() const;

		// ===============================================================================
		
		/// <summary>
		/// Gets the current texture path
		/// </summary>
		/// <returns></returns>
		std::string GetCurrentPath() const;

		// ===============================================================================

	private:

		glm::vec2 pixelSize = { 1,1 };
		int pixelsPerUnit = 100;
		glm::vec2 pivot = { .5f,.5f };
		int zIndex = 0;

		BalisongEngineRenderer::Mesh* quad;
		void CreateOrUpdateQuad();

		BalisongEngineRenderer::Texture2D* texture;
		glm::vec4 tint = { 1,1,1,1 };

		std::string currentPath = "";
	};

}
}