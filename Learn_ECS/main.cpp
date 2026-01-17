/*************************************************************//**
 * @file   main.cpp
 * @brief  The entry point of the program.
 * 
 * Key features:
 * Spawn 100 entities after a certain interval.
 * Display of the number of entity instances and FPS.
 * Draw of falling and rotating entities.
 *
 * Usage:
 * Initialization systems (Physics and Graphics).
 * Registering Components to the System.
 * Spawn 100 entities after a certain interval.
 * Display of the number of entity instances and FPS.
 * Draw of falling and rotating entities.
 * 
 * Dependencies:
 * glad
 * glfw3
 * glm
 *
 * @author HONG Xian Xiang
 * @date   3rd October 2024
 * Copyright 2024, Digipen Institute of Technology
*****************************************************************/

#include "Application.hpp"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Application::Init();
	Application::Run();
	Application::Exit();
	return 0;
}
