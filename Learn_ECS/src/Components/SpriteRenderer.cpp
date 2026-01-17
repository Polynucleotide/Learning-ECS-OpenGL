/*************************************************************//**
 * @file   SpriteRenderer.cpp
 * @brief  Component of type SpriteRenderer of an entity
 *
 * Key features:
 *
 * Usage:
 *
 * Dependencies:
 *
 * @author HONG Xian Xiang
 * @date   3rd October 2024
 * Copyright 2024, Digipen Institute of Technology
*****************************************************************/

#include "Components/SpriteRenderer.hpp"

SpriteRenderer::SpriteRenderer(Texture _sprite) :
	sprite{ _sprite },
	cellWidth{ sprite.mTextureWidth },
	cellHeight{ sprite.mTextureHeight }
{}
