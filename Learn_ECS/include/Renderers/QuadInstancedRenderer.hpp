/*************************************************************//**
 * @file   QuadInstancedRenderer.hpp
 * @brief  Definition of QuadInstancedRenderer and declaration of its static variables and functions.
 * Renderer that contains the VAO, VBO, and EBO for instanced rendering with glDrawElementsInstanced.
 *
 * Key features:
 * Renders quads by MAX_QUADS amount. Each instance of quad will have their own
 * transform matrices, UVs, texture units, and color.
 *
 * Usage:
 *
 * Dependencies:
 *
 * @author HONG Xian Xiang
 * @date   3rd October 2024
 * Copyright 2024, Digipen Institute of Technology
*****************************************************************/

#ifndef QUAD_INSTANCED_RENDERER_HPP
#define QUAD_INSTANCED_RENDERER_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <cstdint>
#include <unordered_map>
#include "Components/Transform.hpp"
#include "Components/SpriteRenderer.hpp"
#include "Alias.hpp"

class QuadInstancedRenderer
{
	private:
		// Maximum instances of quads
		static constexpr size_t MAX_QUADS{ 16384 };
		static constexpr size_t MAX_VERTS{ MAX_QUADS * 4 };

		// Buffer is Structure of Arrays (SoA)
		// So we need their offsets
		static constexpr size_t COLOR_OFFSET{ 0 };
		static constexpr size_t COLOR_ATTR_SIZE{ sizeof(glm::vec4) };
		static constexpr size_t COLOR_DATA_SIZE{ COLOR_ATTR_SIZE * MAX_QUADS };

		static constexpr size_t UV_OFFSET{ COLOR_DATA_SIZE };
		static constexpr size_t UV_ATTR_SIZE{ sizeof(glm::vec2) };
		static constexpr size_t UV_DATA_SIZE{ UV_ATTR_SIZE * MAX_VERTS };

		static constexpr size_t SAMPLER_OFFSET{ UV_OFFSET + UV_DATA_SIZE };
		static constexpr size_t SAMPLER_ATTR_SIZE{ sizeof(GLfloat) };
		static constexpr size_t SAMPLER_DATA_SIZE{ SAMPLER_ATTR_SIZE * MAX_QUADS };

		static constexpr size_t TRANS_OFFSET{ SAMPLER_OFFSET + SAMPLER_DATA_SIZE };
		static constexpr size_t TRANS_ATTR_SIZE{ sizeof(glm::mat3) };
		static constexpr size_t TRANS_DATA_SIZE{ TRANS_ATTR_SIZE * MAX_QUADS };

		static GLuint vao;
		static GLuint vbo;
		static GLfloat samplers[MAX_QUADS];
		static glm::vec2 uvs[MAX_VERTS];
		static glm::mat3 transforms[MAX_QUADS];
		static std::unordered_map<TextureId, GLfloat> texIdToSamplerMap;

		/**
		 * @brief Initialize the shaders for instanced quad rendering
		 */
		static void InitShaders();

		/**
		 * @brief Initialize the buffers for each quad instance
		 */
		static void InitBuffers();

		/**
		 * @brief Calculates the Model-to-World matrix from the Transform component which
		 * will be sent to the GPU.
		 * @param[in,out] transform A reference to a 3x3 Matrix which will be sent to the GPU.
		 * @param[in]     component A read-only reference to the Transform component.
		 */
		static void CalculateTransform(glm::mat3& transform, Transform const& component);

		/**
		 * @brief Calculates the UVs for all 4 vertices for each quad, using the given sprite sheet.
		 * @param[in,out] uv A pointer to the UV value of the first vertex.
		 * @param[in]     component A read-only reference to the SpriteRenderer component.
		 */
		static void CalculateUVs(glm::vec2* uv, SpriteRenderer const& component);

		/**
		 * @brief Activate texture units for the shader.
		 */
		static void ActivateTextureUnits();

		/**
		 * @brief Invokes a draw call when one of three conditions happen.
		 * 1. When batch count hits MAX_QUADS
		 * 2. When it is the final batch
		 * 3. When it runs out of texture slots
		 */
		static void Flush(size_t count);

	public:
		/**
		 * @brief Initialize shaders and buffers
		 */
		static void Init();

		/**
		 * @brief Render the quads
		 */
		static void Render();

		/**
		 * @brief Deletes the shader and VAO
		 */
		static void Free();
};

#endif // !QUAD_INSTANCED_RENDERER_HPP
