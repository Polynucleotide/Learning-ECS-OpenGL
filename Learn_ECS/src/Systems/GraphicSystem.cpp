#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include "Systems/GraphicSystem.hpp"
#include "Managers/ArchetypeManager.hpp"
#include "Managers/EntityManager.hpp"
#include "Managers/AssetManager.hpp"
#include "Components/SpriteRenderer.hpp"
#include "Components/Transform.hpp"
#include "Renderers/QuadInstancedRenderer.hpp"
#include "Application.hpp"
#include "Shader.hpp"

/**
 * @brief Initialize batch size. Create shader program and VAO
 */
void GraphicSystem::Init()
{
	std::cout << __FUNCTION__ << '\n';
	glClearColor(1.f, 1.f, 1.f, 1.f);

	QuadInstancedRenderer::Init();
}

void GraphicSystem::Update()
{
	//std::cout << __FUNCTION__ << '\n';
}

/**
 * @brief Renders objects to the screen.
 */
void GraphicSystem::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	QuadInstancedRenderer::Render();
}

/**
 * @brief Frees memory allocated for shader program and VAOs.
 */
void GraphicSystem::Free()
{
	QuadInstancedRenderer::Free();
}
