/*************************************************************//**
 * @file   SpriteRenderer.hpp
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

#ifndef SPRITE_RENDERER_HPP
#define SPRITE_RENDERER_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Components/Texture.hpp"
#include "Interfaces/IComponent.hpp"
#include "Alias.hpp"

struct SpriteRenderer : public IComponent
{
	Texture sprite;
	GLint cellWidth;
	GLint cellHeight;
	GLint row{ 0 }, col{ 0 };
	bool flipX{ false };
	bool flipY{ false };

	SpriteRenderer(Texture _sprite);
};

#endif // !SPRITE_RENDERER_HPP
