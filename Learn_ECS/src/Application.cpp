/*************************************************************//**
 * @file   Application.cpp
 * @brief  Application to store static variables like
 * window size and NDC matrix.
 *
 * Key features:
 *
 * Usage:
 * Application::WIDTH or Application::HEIGHT to get the window's dimensions
 *
 * Dependencies:
 *
 * @author HONG Xian Xiang
 * @date   3rd October 2024
 * Copyright 2024, Digipen Institute of Technology
*****************************************************************/

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <memory>

#include "Application.hpp"
#include "Time.hpp"

#include "Managers/SystemManager.hpp"
#include "Managers/EntityManager.hpp"
#include "Managers/ComponentManager.hpp"
#include "Managers/AssetManager.hpp"

#include "Components/Transform.hpp"
#include "Components/Rigidbody2D.hpp"
#include "Components/SpriteRenderer.hpp"
#include "Components/Texture.hpp"
#include "Components/Animator.hpp"

#include "Systems/InputSystem.hpp"
#include "Systems/PhysicsSystem.hpp"
#include "Systems/GraphicSystem.hpp"
#include "Systems/AnimatorSystem.hpp"
#include "Systems/MonoBehaviourSystem.hpp"

#include "Scripts/Zombie.hpp"

#include "Utilities/Random.hpp"

// Define static variables
GLFWwindow* Application::ptrWindow{ nullptr };
glm::mat3 Application::worldToNDCMatrix{ glm::mat3(1.f) };
GLint Application::maxTextureUnits{ 0 };

/**
 * @brief Get the singleton instance
 */
Application& Application::GetInstance()
{
	static Application instance;
	return instance;
}

/**
 * @brief Initialize engine
 */
void Application::Init()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	unsigned int r1{ static_cast<unsigned int>(rand()) };
	unsigned int r2{ static_cast<unsigned int>(rand()) };
	unsigned int seed{ r1 * r2 + r1 + r2 };
	srand(seed);
	InitOpenGL();
	ComponentManager::GetInstance().Init();
	GraphicSystem::GetInstance().Init();

	SystemManager::AddSystem(
		std::make_shared<MonoBehaviourSystem>(),
		"MonoBehaviourSystem"
	);
	SystemManager::AddSystem(
		std::make_shared<AnimatorSystem>(),
		"AnimatorSystem"
	);
	SystemManager::InitSystems();
}

/**
 * @brief Initialize OpenGL
 */
void Application::InitOpenGL()
{
	// Context
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	ptrWindow = glfwCreateWindow(Application::WIDTH, Application::HEIGHT, "TMDB", NULL, NULL);
	if (ptrWindow == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(ptrWindow);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(EXIT_FAILURE);
	}

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Window
	glViewport(0, 0, Application::WIDTH, Application::HEIGHT);

	// Get OpenGL max values
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnits);
	std::cout << "MAX TEXTURE UNITS: " << maxTextureUnits << '\n';
}

/**
 * @brief Starts the game loop
 */
void Application::Run()
{
	InputSystem& inputSystem{ InputSystem::GetInstance() };
	GraphicSystem& graphicSystem{ GraphicSystem::GetInstance() };
	PhysicsSystem& physicsSystem{ PhysicsSystem::GetInstance() };
	EntityManager& entityManager{ EntityManager::GetInstance() };

	// Zombie textures
	Texture const& texture1 = AssetManager::GetInstance().LoadTexture("Assets/EternityPainter.png");
	Texture const& texture2 = AssetManager::GetInstance().LoadTexture("Assets/Panddo.png");

	// Load entities
	Entity& entity{ entityManager.CreateEntity() };
	entityManager.AddComponent<Transform>(entity, Transform{ 0.f, 0.f, 0.f, 500.f, 500.f });
	entityManager.AddComponent<SpriteRenderer>(entity, SpriteRenderer{ texture1 });
	entityManager.AddComponent<Animator>(entity, Animator{});
	entityManager.AddComponent<Zombie>(entity, Zombie{}); // TODO maybe change this (MonoBehaviour base class points to this instead?)

	// Set cell
	SpriteRenderer* sr{ nullptr };
	sr = entityManager.GetComponent<SpriteRenderer>(entity, &sr);
	sr->cellWidth = 100;
	sr->cellHeight = 100;

	// Define sprite animation
	Animator* animator{ nullptr };
	animator = entityManager.GetComponent<Animator>(entity, &animator);
	animator->AddAnimation("Walk");
	Animation& animation{ animator->GetAnimation("Walk") };
	animation.AddFrame(9, 0);
	animation.AddFrame(8, 0);
	animation.AddFrame(7, 0);
	animation.AddFrame(6, 0);
	animation.AddFrame(5, 0);
	animation.AddFrame(4, 0);
	animation.AddFrame(3, 0);
	animation.AddFrame(2, 0);
	animator->Play("Walk");

	// Call Start() to all MonoBehaviours
	auto& monoBehaviourSystem{ SystemManager::GetSystem("MonoBehaviourSystem")};
	monoBehaviourSystem->Init();

	double timer1{ 0.0 };
	double timer2{ 0.0 };
	while (!glfwWindowShouldClose(Application::GetWindow()))
	{
		Time::Update();
		glfwPollEvents();

#if 1
		// Spawn entities
		// TODO remove this
		timer1 += Time::deltaTime;
		if (timer1 >= 1.0)
		{
			for (int i{}; i < 10000; ++i)
			{
				Entity& entity2{ entityManager.CreateEntity() };
				float x{ Random::RandomFloat(-Application::WIDTH / 2.f, Application::WIDTH / 2.f) };
				float y{ Application::HEIGHT / 2.f + Random::RandomFloat(50.f, 100.f) };
				float a{ Random::RandomFloat(-3.1415f / 18.f, 3.1415f / 18.f) };
				entityManager.AddComponent<Transform>(entity2, Transform{ x, y, a, 100.f, 100.f });
				entityManager.AddComponent<Rigidbody2D>(entity2, Rigidbody2D{ 50.f, 50.f });
				entityManager.AddComponent<SpriteRenderer>(entity2, SpriteRenderer{ texture2 });
				sr = entityManager.GetComponent<SpriteRenderer>(entity2, &sr);
				sr->cellWidth = 32;
				sr->cellHeight = 32;
			}
			timer1 = 0.0;
		}

		// FPS
		// TODO remove this
		timer2 += Time::deltaTime;
		if (timer2 >= 1.0)
		{
			std::cout << "Objects: " << entityManager.GetEntityCount() << " | FPS: " << (1.0 / Time::deltaTime) << "\n";
			timer2 = 0.0;
		}
#endif

		// [x] Input
		// [x] Physics
		// [ ] Collision
		// [x] Other Systems
		// [ ] Physics
		// [x] Graphics
		// [x] Draw

		inputSystem.Update();
		physicsSystem.Update();
		SystemManager::UpdateSystems();
		Application::Update();
		graphicSystem.Update();
		graphicSystem.Draw();

		glfwSwapBuffers(Application::GetWindow());
	}
}

/**
 * @brief Updates world to NDC matrix
 */
void Application::Update()
{
	worldToNDCMatrix = {
		2.f / WIDTH, 0.f,          0.f,
		0.f,         2.f / HEIGHT, 0.f,
		0.f,         0.f,          1.f
	};
}

/**
 * @brief Free allocated memory
 */
void Application::Exit()
{
	GraphicSystem::GetInstance().Free();
	glfwTerminate();
}

GLFWwindow* Application::GetWindow()
{
	return ptrWindow;
}

glm::mat3 const& Application::GetWorldToNDCMatrix()
{
	return worldToNDCMatrix;
}

GLint Application::GetMaxTextureUnits()
{
	return maxTextureUnits;
}
