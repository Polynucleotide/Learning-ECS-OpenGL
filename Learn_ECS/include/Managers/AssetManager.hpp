/*************************************************************//**
 * @file   AssetManager.hpp
 * @brief  Definition of AssetManager, which stores all the textures.
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

#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP

#include <glad/glad.h>
#include <unordered_map>
#include <string>
#include "Alias.hpp"
#include "Components/Texture.hpp"

class AssetManager
{
	public:
		/**
		 * @brief Gets the reference to the singleton instance
		 */
		static AssetManager& GetInstance()
		{
			static AssetManager instance;
			return instance;
		}

		/**
		 * @brief Delete copy constructor and assignment operator because singleton.
		 */
		AssetManager(AssetManager const&) = delete;
		AssetManager& operator=(AssetManager const&) = delete;

		/**
		 * @brief Loads a texture, given a file path
		 * @param[in] path Path name of the desiredtexture
		 * @return Reference to the loaded texture
		 */
		Texture& LoadTexture(std::string const& path);

	private:
		AssetManager() = default;

		std::unordered_map<std::string, TextureId> mStringToTextureIdMap;
		std::unordered_map<TextureId, Texture> mTextureIdToTextureMap;
};

#endif // !ASSET_MANAGER_HPP
