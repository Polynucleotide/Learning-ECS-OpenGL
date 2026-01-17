/*************************************************************//**
 * @file   QuadInstancedRenderer.cpp
 * @brief  Definition of static variables and functions.
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

#include <vector>
#include <cstdint>
#include <iostream>
#include <algorithm>
#include "Renderers/QuadInstancedRenderer.hpp"
#include "Managers/ArchetypeManager.hpp"
#include "Components/Transform.hpp"
#include "Components/SpriteRenderer.hpp"
#include "Application.hpp"
#include "Shader.hpp"

GLuint QuadInstancedRenderer::vao{ 0 };
GLuint QuadInstancedRenderer::vbo{ 0 };
GLfloat QuadInstancedRenderer::samplers[MAX_QUADS];
glm::vec2 QuadInstancedRenderer::uvs[MAX_VERTS];
glm::mat3 QuadInstancedRenderer::transforms[MAX_QUADS];
std::unordered_map<TextureId, GLfloat> QuadInstancedRenderer::texIdToSamplerMap;

/**
 * @brief Initialize shaders and buffers
 */
void QuadInstancedRenderer::Init()
{
	InitShaders();
	InitBuffers();
}

/**
 * @brief Initialize the shaders for instanced quad rendering
 */
void QuadInstancedRenderer::InitShaders()
{
	Shader& quadInstancedShader{ Shader::LoadShader("Assets/Shaders/quad.vert", "Assets/Shaders/quad.frag", "QuadInstancedShader") };
	quadInstancedShader.AddUniform("u_world_to_ndc_mtx");
	quadInstancedShader.AddUniform("uSamplers");
}

/**
 * @brief Initialize the buffers for each quad instance
 */
void QuadInstancedRenderer::InitBuffers()
{
	// VBO
	glCreateBuffers(1, &vbo);
	glNamedBufferStorage(
		vbo,
		COLOR_DATA_SIZE + UV_DATA_SIZE +
		SAMPLER_DATA_SIZE + TRANS_DATA_SIZE,
		nullptr,
		GL_DYNAMIC_STORAGE_BIT
	);

	// VAO
	glCreateVertexArrays(1, &vao);

	// Color
	glEnableVertexArrayAttrib(vao, 0);
	glVertexArrayVertexBuffer(vao, 0, vbo, COLOR_OFFSET, static_cast<GLsizei>(COLOR_ATTR_SIZE));
	glVertexArrayAttribFormat(vao, 0, 4, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vao, 0, 0);
	glVertexArrayBindingDivisor(vao, 0, 1);

	// UV
	glEnableVertexArrayAttrib(vao, 1);
	glVertexArrayVertexBuffer(vao, 1, vbo, UV_OFFSET, static_cast<GLsizei>(UV_ATTR_SIZE));
	glVertexArrayAttribFormat(vao, 1, 2, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vao, 1, 1);

	// Sampler
	glEnableVertexArrayAttrib(vao, 2);
	glVertexArrayVertexBuffer(vao, 2, vbo, SAMPLER_OFFSET, static_cast<GLsizei>(SAMPLER_ATTR_SIZE));
	glVertexArrayAttribFormat(vao, 2, 1, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vao, 2, 2);
	glVertexArrayBindingDivisor(vao, 2, 1);

	// Transform
	glVertexArrayVertexBuffer(vao, 3, vbo, TRANS_OFFSET, static_cast<GLsizei>(TRANS_ATTR_SIZE));
	glEnableVertexArrayAttrib(vao, 3);
	glEnableVertexArrayAttrib(vao, 4);
	glEnableVertexArrayAttrib(vao, 5);
	glVertexArrayAttribFormat(vao, 3, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribFormat(vao, 4, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3));
	glVertexArrayAttribFormat(vao, 5, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3) * 2);
	glVertexArrayAttribBinding(vao, 3, 3);
	glVertexArrayAttribBinding(vao, 4, 3);
	glVertexArrayAttribBinding(vao, 5, 3);
	glVertexArrayBindingDivisor(vao, 3, 1);
	glVertexArrayBindingDivisor(vao, 4, 1);
	glVertexArrayBindingDivisor(vao, 5, 1);

	// EBO
	GLubyte indices[4]{ 0, 1, 2, 3 };
	GLuint ebo;
	glCreateBuffers(1, &ebo);
	glNamedBufferStorage(ebo, sizeof(indices), indices, GL_DYNAMIC_STORAGE_BIT);
	glVertexArrayElementBuffer(vao, ebo);

	glBindVertexArray(0);
}

/**
 * @brief Render the quads
 */
void QuadInstancedRenderer::Render()
{
	ArchetypeManager& am{ ArchetypeManager::GetInstance() };
	ArchetypeSet set{ am.GetArchetypeSet<Transform, SpriteRenderer>() };

	// Initialize uniform sampler array
	GLint maxTextureUnits{ Application::GetMaxTextureUnits() };
	std::vector<GLint> uSamplers(maxTextureUnits);
	for (size_t i{}; i < uSamplers.size(); ++i)
		uSamplers[i] = static_cast<GLint>(i);

	Shader* quadShader{ Shader::GetShader("QuadInstancedShader") };
	glUseProgram(quadShader->GetId());
	glBindVertexArray(vao);

	quadShader->SetUniform("uSamplers", maxTextureUnits, uSamplers.data());
	quadShader->SetUniform("u_world_to_ndc_mtx", &Application::GetWorldToNDCMatrix()[0][0]);

	for (auto& arch : set)
	{
		auto& tv{ arch->GetComponentArray<Transform>() };
		auto& srv{ arch->GetComponentArray<SpriteRenderer>() };

		size_t entityCount{ arch->GetEntityCount() };
		size_t instCount{}, vertCount{};
		for (size_t i{}; i < entityCount; ++i)
		{
			Transform const& t{ std::any_cast<Transform&>(tv[i]) };
			CalculateTransform(transforms[instCount], t);

			SpriteRenderer const& sr{ std::any_cast<SpriteRenderer&>(srv[i]) };
			CalculateUVs(&uvs[vertCount], sr);

			texIdToSamplerMap.insert({ sr.sprite.mId, static_cast<GLfloat>(texIdToSamplerMap.size()) });
			samplers[instCount] = texIdToSamplerMap[sr.sprite.mId];

			++instCount;
			vertCount += 4;

			// Flush if
			// 1. Batch size reached
			// 2. Last batch reached
			// 3. Out of texture units
			if (instCount >= MAX_QUADS ||
				(i + 1) >= entityCount ||
				texIdToSamplerMap.size() >= maxTextureUnits)
			{
				ActivateTextureUnits();
				Flush(instCount);
				instCount = 0;
				vertCount = 0;
				texIdToSamplerMap.clear();
			}
		}
	}
	glBindVertexArray(0);
	glUseProgram(0);
}

/**
 * @brief Calculates the Model-to-World matrix from the Transform component which
 * will be sent to the GPU.
 * @param[in,out] transform A reference to a 3x3 Matrix which will be sent to the GPU.
 * @param[in]     component A read-only reference to the Transform component.
 */
void QuadInstancedRenderer::CalculateTransform(glm::mat3& transform, Transform const& t)
{
	glm::mat3 scale{
		t.w, 0.f, 0.f,
		0.f, t.h, 0.f,
		0.f, 0.f, 1.f
		};
	glm::mat3 rotate{
		cosf(t.a), sinf(t.a), 0.f,
		-sinf(t.a), cosf(t.a), 0.f,
		0.f, 0.f, 1.f
	};
	glm::mat3 translate{
		1.f, 0.f, 0.f,
		0.f, 1.f, 0.f,
		t.x, t.y, 1.f
	};
	transform = translate * rotate * scale;
}

/**
 * @brief Calculates the UVs for all 4 vertices for each quad, using the given sprite sheet.
 * @param[in,out] uv A pointer to the UV value of the first vertex.
 * @param[in]     component A read-only reference to the SpriteRenderer component.
 */
void QuadInstancedRenderer::CalculateUVs(glm::vec2* uv, SpriteRenderer const& sr)
{
	GLfloat w{ static_cast<GLfloat>(sr.cellWidth)  / sr.sprite.mTextureWidth };
	GLfloat h{ static_cast<GLfloat>(sr.cellHeight) / sr.sprite.mTextureHeight };
	GLfloat x = sr.col * w;
	GLfloat y = sr.row * h;

	glm::vec2 topLeft{ x, y + h };
	glm::vec2 bottomLeft{ x, y };
	glm::vec2 topRight{ x + w, y + h };
	glm::vec2 bottomRight{ x + w, y };

	if (sr.flipX)
	{
		std::swap(topLeft, topRight);
		std::swap(bottomLeft, bottomRight);
	}

	if (sr.flipY)
	{
		std::swap(topLeft, bottomLeft);
		std::swap(topRight, bottomRight);
	}

	*(uv + 0) = topLeft;
	*(uv + 1) = bottomLeft;
	*(uv + 2) = topRight;
	*(uv + 3) = bottomRight;
}

/**
 * @brief Activate texture units for the shader.
 */
void QuadInstancedRenderer::ActivateTextureUnits()
{
	for (auto& [textureId, sampler] : texIdToSamplerMap)
	{
		glActiveTexture(GL_TEXTURE0 + static_cast<int>(sampler));
		glBindTexture(GL_TEXTURE_2D, textureId);
	}
}

/**
 * @brief Invokes a draw call when one of three conditions happen.
 * 1. When batch count hits MAX_QUADS
 * 2. When it is the final batch
 * 3. When it runs out of texture slots
 */
void QuadInstancedRenderer::Flush(size_t count)
{
	glNamedBufferSubData(vbo, UV_OFFSET, UV_ATTR_SIZE * count * 4, uvs);
	glNamedBufferSubData(vbo, SAMPLER_OFFSET, SAMPLER_ATTR_SIZE * count, samplers);
	glNamedBufferSubData(vbo, TRANS_OFFSET, TRANS_ATTR_SIZE * count, transforms);
	glDrawElementsInstanced(
		GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE,
		nullptr, static_cast<GLsizei>(count)
	);
}

/**
 * @brief Deletes the shader and VAO
 */
void QuadInstancedRenderer::Free()
{
	glDeleteProgram(Shader::GetShader("QuadInstancedShader")->GetId());
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	vao = vbo = 0;
}
