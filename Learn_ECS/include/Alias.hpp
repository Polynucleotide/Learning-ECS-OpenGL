/*************************************************************//**
 * @file   Alias.hpp
 * @brief  Just a file to store aliases so we don't have to write really long types
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

#ifndef ALIAS_HPP
#define ALIAS_HPP

#include <glad/glad.h>
#include <cstdint>
#include <bitset>
#include <vector>
#include <any>

class Archetype;

constexpr size_t MAX_COMPONENTS = 16;
constexpr size_t MAX_ENTITIES = 4'096;
using EntityId = uint32_t;
using TextureId = GLuint;
using Signature = std::bitset<MAX_COMPONENTS>;
using ComponentArray = std::vector<std::any>; // TODO Change to std::variant if components are < 64 bytes
using ArchetypeSet = std::vector<Archetype*>;

#endif // ! ALIAS_HPP
