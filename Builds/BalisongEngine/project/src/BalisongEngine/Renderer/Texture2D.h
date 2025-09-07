#pragma once
#include "BaseResource.h"
#include <string>
#include <glm/vec2.hpp>

// ===============================================================================

namespace BalisongEngine{
namespace BalisongEngineRenderer
{
	/// <summary>
	/// The wrapping mode for textures along an axis
	/// </summary>
	enum class TextureWrapMode
	{
		REPEAT,
		CLAMP,
	};
	/// <summary>
	/// The filtering mode used when sampling a texture
	/// </summary>
	enum class TextureFilterMode
	{
		LINEAR,
		NEAREST,
	};

	/// <summary>
	/// Preset for a texture, like wrapping and filtering modes
	/// </summary>
	struct TextureConfig
	{
		/// <summary>
		/// The wrapping mode for the texture on the x axis
		/// </summary>
		TextureWrapMode wrapModeX;
		/// <summary>
		/// The wrapping mode for the texture on the y axis
		/// </summary>
		TextureWrapMode wrapModeY;
		/// <summary>
		/// The filtering mode to use when sampling the texture
		/// </summary>
		TextureFilterMode filterMode;
		/// <summary>
		/// If mipmaps should be generated and used for the texture (doesn't work)
		/// </summary>
		bool useMipmaps = false;
	};

	// ===============================================================================

	/// <summary>
	/// A texture resource that can be used in rendering
	/// </summary>
	class Texture2D : public BalisongEngineAllocator::BaseResource
	{
	public:

		/// <summary>
		/// ctor
		/// </summary>
		/// <param name="path"></param>
		/// <param name="cfg"></param>
		Texture2D(const std::string& path, TextureConfig cfg);
		~Texture2D();

		/// <summary>
		/// Gets a blank texture
		/// </summary>
		/// <returns>Texture2D</returns>
		static Texture2D* BlankTexture();

		// ===============================================================================

		/// <summary>
		/// Gets the texture's ID
		/// </summary>
		/// <returns>int id</returns>
		unsigned int GetID() const;
		/// <summary>
		/// Gets the texture's size
		/// </summary>
		/// <returns>vec2 size</returns>
		glm::ivec2 GetSize() const;
		/// <summary>
		/// Gets the texture path
		/// </summary>
		/// <returns>string path</returns>
		const std::string& GetPath() const;
		/// <summary>
		/// Gets the texture's TextureConfig
		/// </summary>
		/// <returns>TextureConfig</returns>
		const TextureConfig& GetConfig() const;

		// ===============================================================================

		/// <summary>
		/// Sets the TextureWrapMode
		/// </summary>
		/// <param name="wrap_mode_x">x</param>
		/// <param name="wrap_mode_y">y</param>
		void SetWrapMode(TextureWrapMode wrap_mode_x, TextureWrapMode wrap_mode_y);
		/// <summary>
		/// Sets the TextureFilterMode, and toggles Mipmaps
		/// </summary>
		/// <param name="filter_mode">filterMode</param>
		/// <param name="use_mipmaps">useMipmaps</param>
		void SetFilterMode(TextureFilterMode filter_mode, bool use_mipmaps);

		/// <summary>
		/// Combine SetWrapMode and SetFilterMode together
		/// </summary>
		/// <param name="cfg_">TextureConfig</param>
		void SetTextureConfig(TextureConfig cfg_);

		// ===============================================================================

	private:

		TextureConfig cfg;
		std::string path;
		unsigned int id;
		int width;
		int height;

	};

}
}