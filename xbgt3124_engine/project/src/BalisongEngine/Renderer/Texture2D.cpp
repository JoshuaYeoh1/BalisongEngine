#pragma once
#include "Texture2D.h"
using namespace BalisongEngine;
using namespace BalisongEngineRenderer;

//#include "BaseResource.h" // in header
using namespace BalisongEngineAllocator;

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

#include <iostream>
using namespace std;

// ===============================================================================

static GLint toGLFormat_WrapMode(TextureWrapMode wrap_mode)
{
	switch (wrap_mode)
	{
	case TextureWrapMode::REPEAT: return GL_REPEAT;
	case TextureWrapMode::CLAMP: return GL_CLAMP;
	}
	return 0;
}

static GLint toGLFormat_MagFilter(TextureFilterMode filter_mode, bool use_mipmaps)
{
	switch (filter_mode)
	{
	case TextureFilterMode::LINEAR: return use_mipmaps ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR;
	case TextureFilterMode::NEAREST: return use_mipmaps ? GL_NEAREST_MIPMAP_NEAREST : GL_NEAREST;
	}
	return 0;
}

static GLint toGLFormat_MinFilter(TextureFilterMode filter_mode, bool use_mipmaps)
{
	switch (filter_mode)
	{
	case TextureFilterMode::LINEAR: return use_mipmaps ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR;
	case TextureFilterMode::NEAREST: return use_mipmaps ? GL_NEAREST_MIPMAP_NEAREST : GL_NEAREST;
	}
	return 0;
}

// ===============================================================================

void Texture2D::SetWrapMode(TextureWrapMode wrap_mode_x, TextureWrapMode wrap_mode_y)
{
	cfg.wrapModeX = wrap_mode_x;
	cfg.wrapModeY = wrap_mode_y;

	glBindTexture(GL_TEXTURE_2D, id);

	// Set the new wrap modes
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, toGLFormat_WrapMode(cfg.wrapModeX));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, toGLFormat_WrapMode(cfg.wrapModeY));
}

void Texture2D::SetFilterMode(TextureFilterMode filter_mode, bool use_mipmaps)
{
	cfg.filterMode = filter_mode;
	cfg.useMipmaps = use_mipmaps;

	glBindTexture(GL_TEXTURE_2D, id);

	// Set the new filter modes
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, toGLFormat_MinFilter(cfg.filterMode, use_mipmaps));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, toGLFormat_MagFilter(cfg.filterMode, use_mipmaps));
}

void Texture2D::SetTextureConfig(TextureConfig cfg_)
{
	SetWrapMode(cfg_.wrapModeX, cfg_.wrapModeY);
	SetFilterMode(cfg_.filterMode, cfg_.useMipmaps);
}

// ===============================================================================

Texture2D* Texture2D::BlankTexture()
{
	TextureConfig cfg;
	cfg.wrapModeX = TextureWrapMode::REPEAT;
	cfg.wrapModeY = TextureWrapMode::REPEAT;
	cfg.filterMode = TextureFilterMode::LINEAR;
	cfg.useMipmaps = false;

	static Texture2D* blank_tex = new Texture2D("blank", cfg);

	return blank_tex;
}

// ===============================================================================

Texture2D::Texture2D(const string& path, TextureConfig cfg) : BaseResource(ResourceType::TEXTURE), path(path), cfg(cfg), id(0), width(0), height(0)
{
	int w, h, channels;

	// Flip the image vertically
	stbi_set_flip_vertically_on_load(1);

	// Load image data
	unsigned char* data = stbi_load(path.c_str(), &w, &h, &channels, 0);

	if (data)
	{
		GLenum internal_format = 0;
		GLenum data_format = 0;

		if (channels == 4)
		{
			// internalFormat is GL_RGBA8
			internal_format = GL_RGBA8;
			// dataFormat is GL_RGBA
			data_format = GL_RGBA;
		}
		else if (channels == 3)
		{
			// internalFormat is GL_RGB8
			internal_format = GL_RGB8;
			// dataFormat is GL_RGB
			data_format = GL_RGB;
		}

		// generate 1 texture, pass id as reference
		glGenTextures(1, &id);
		// bind the texture
		glBindTexture(GL_TEXTURE_2D, id);

		// set wrap modes
		// use toGLFormat_WrapMode to convert TextureWrapMode to GL equivalent
		SetWrapMode(cfg.wrapModeX, cfg.wrapModeY);

		// set filter modes
		// use toGLFormat_MagFilter and toGLFormat_MinFilter to convert
		// TextureFilterMode to GL equivalent
		SetFilterMode(cfg.filterMode, cfg.useMipmaps);

		// upload texture data
		// refer to OpenGL documentation on what goes where
		glTexImage2D(GL_TEXTURE_2D, 0, internal_format, w, h, 0, data_format, GL_UNSIGNED_BYTE, data);

		if (cfg.useMipmaps)
		{
			//glGenerateMipmap(GL_TEXTURE_2D); // doesnt work???
		}

		// free memory as image data is uploaded to GPU
		stbi_image_free(data);

		width = w;
		height = h;

		// log success
		cout << "[Texture2D] Image loaded: " << path.c_str() << endl;
	}
	else
	{
		// log error
		cout << "[Texture2D] Failed to load image: " << path.c_str() << endl;
	}
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &id);
}

// ===============================================================================

unsigned int Texture2D::GetID() const
{
	return id;
}
glm::ivec2 Texture2D::GetSize() const
{
	return glm::ivec2(width, height);
}
const string& Texture2D::GetPath() const
{
	return path;
}
const TextureConfig& Texture2D::GetConfig() const
{
	return cfg;
}


