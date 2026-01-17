/*************************************************************//**
 * @file   AssetManager.cpp
 * @brief  Function definitions of AssetManager, which stores all the textures.
 *
 * Key features:
 * Stores all textures
 *
 * Usage:
 * Texture& texture = LoadTexture("Assets/Sprite.png");
 *
 * Dependencies:
 *
 * @author HONG Xian Xiang
 * @date   8th November 2024
 * Copyright 2024, Digipen Institute of Technology
*****************************************************************/

#include <iostream>
#include "Managers/AssetManager.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

/**
 * @brief Loads a texture, given a file path
 * @param[in] path Path name of the desiredtexture
 * @return Reference to the loaded texture
 */
Texture& AssetManager::LoadTexture(std::string const& path)
{
	// If texture already exist
	auto it{ mStringToTextureIdMap.find(path) };
	if (it != std::end(mStringToTextureIdMap))
		return mTextureIdToTextureMap[it->second];

	stbi_set_flip_vertically_on_load(1);

	int width, height, nrChannels;
	stbi_uc* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

	if (!data)
	{
		std::cout << "Failed to load texture.\n";
		exit(0);
	}

	TextureId tex;
	glCreateTextures(GL_TEXTURE_2D, 1, &tex);
	glTextureParameteri(tex, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(tex, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTextureParameteri(tex, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTextureParameteri(tex, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateTextureMipmap(tex);
	glTextureStorage2D(tex, 1, GL_RGBA8, width, height);
	glTextureSubImage2D(tex, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
	stbi_image_free(data);

	mStringToTextureIdMap[path] = tex;
	mTextureIdToTextureMap[tex] = Texture{ tex, width, height };

	return mTextureIdToTextureMap[tex];
}
