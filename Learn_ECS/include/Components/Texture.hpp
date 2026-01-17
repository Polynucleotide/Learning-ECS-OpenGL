/*************************************************************//**
 * @file   Texture.hpp
 * @brief  Definition of the Texture. Not really a component,
 * just a supporting struct for SpriteRenderer component
 *
 * Key features:
 * Stores texture information. Its ID, width, and height.
 * Width and height is used to calculate UVs.
 *
 * Usage:
 *
 * Dependencies:
 *
 * @author HONG Xian Xiang
 * @date   8th November 2024
 * Copyright 2024, Digipen Institute of Technology
*****************************************************************/

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "Alias.hpp"

struct Texture
{
	TextureId mId;
	GLint mTextureWidth;
	GLint mTextureHeight;
};

#endif // !TEXTURE_HPP
