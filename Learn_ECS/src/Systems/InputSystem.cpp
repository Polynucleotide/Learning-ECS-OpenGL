/*****************************************************************//**
 * @file   InputSystem.cpp
 * @brief Defines the input system for handling keyboard and mouse inputs.
 *
 * The `InputSystem` class manages the detection of user input
 * through the keyboard and mouse. It handles key states (down,
 * triggered, and released) and mouse button states, and tracks mouse
 * position.
 *
 * Key features:
 * - Supports detection of key presses and mouse button actions.
 * - Tracks both key states and mouse button states.
 * - Allows the user to obtain current and delta mouse positions.
 *
 * Usage:
 * - isKeyDown() to check if a key is currently pressed.
 * - isKeyTriggered() to detect if a key has been pressed in the
 *   current frame.
 * - isMouseDown() and isMouseClick() for mouse button interactions.
 * - Update() is called each frame to update input states and mouse position.
 *
 * Dependencies:
 *
 *
 * @author Darius Khoo
 * @date   3/10/2024
 * Copyright 2024, Digipen Institute of Technology
 *********************************************************************/
#include <iostream>
#include "Application.hpp"
#include "Systems/InputSystem.hpp"

std::vector<InputSystem::KeyState> InputSystem::keyState(Key::TOTAL_KEYS, RELEASE);
std::vector<InputSystem::KeyState> InputSystem::mouseState(MouseButton::TOTAL_BUTTONS, RELEASE);
std::pair<double, double> InputSystem::mousePos{ 0., 0. };
std::pair<double, double> InputSystem::previousMousePos{ 0., 0. };

/*!
* @brief Checks if a specified key is currently pressed down.
*
* @param key - The key to check.
* @return True if the key is pressed down, false otherwise.
*//*______________________________________________________________*/
bool InputSystem::KeyDown(Key key)
{
	if (key >= Key::A && key <= Key::Z)
	{
		return keyState[static_cast<int>(key - Key::A)] == DOWN;
	}
	else
	{
		return keyState[static_cast<int>(key - NUM_0 + TOTAL_LETTERS)] == DOWN;
	}
}

/*!
* @brief Checks if a specified key has just been pressed.
*
* @param key - The key to check.
* @return True if the key was just pressed, false otherwise.
*//*______________________________________________________________*/
bool InputSystem::KeyTriggered(Key key)
{
	if (key >= Key::A && key <= Key::Z)
	{
		return keyState[static_cast<int>(key - Key::A)] == TRIGGERED;
	}
	else
	{
		return keyState[static_cast<int>(key - NUM_0 + TOTAL_LETTERS)] == TRIGGERED;
	}
}

/*!
* @brief Checks if a specified mouse button is currently pressed down.
*
* @param mouseButton - The mouse button to check.
* @return True if the mouse button is pressed down, false otherwise.
*//*______________________________________________________________*/
bool InputSystem::MouseDown(MouseButton mouseButton)
{
	return mouseState[mouseButton] == DOWN;
}

/*!
* @brief Checks if a specified mouse button has just been clicked.
*
* @param mouseButton - The mouse button to check.
* @return True if the mouse button was just clicked, false otherwise.
*//*______________________________________________________________*/
bool InputSystem::MouseClick(MouseButton mouseButton)
{
	return mouseState[mouseButton] == TRIGGERED;
}

/*!
* @brief Gets the current mouse position.
* 
* @return Current mouse position as Vector2
*//*______________________________________________________________*/
Vector2 InputSystem::GetMousePosition()
{
	return Vector2{ static_cast<float>(mousePos.first), static_cast<float>(mousePos.second) };
}

/*!
* @brief Gets the difference between the current and previous mouse position.
* 
* @return Difference between mouse positions from the previous frame as Vector2
*//*______________________________________________________________*/
Vector2 InputSystem::GetMousePositionDelta()
{
	float dx = static_cast<float>(mousePos.first - previousMousePos.first);
	float dy = static_cast<float>(mousePos.second - previousMousePos.second);
	return Vector2{ dx, dy };
}

/*!
* @brief Updates the input system each frame, tracking key states and mouse position.
*//*______________________________________________________________*/
void InputSystem::Update()
{
	previousMousePos.first = mousePos.first;
	previousMousePos.second = mousePos.second;

	GLFWwindow* ptrWindow{ Application::GetInstance().GetWindow() };
	glfwGetCursorPos(ptrWindow, &mousePos.first, &mousePos.second);

	for (char i = Key::A; i <= Key::Z; ++i)
	{
		int vectorIndex = i - Key::A;
		bool isKeyDown = (glfwGetKey(ptrWindow, i) == GLFW_PRESS);
		KeyState lastKeyState = keyState[vectorIndex];

		if (isKeyDown)
		{
			//if (lastKeyState != DOWN && PhysicsSystem::GetInstance()->GetStepByStep())
			//{
			//	PhysicsSystem::GetInstance()->SetisUpdated(false);
			//}
			keyState[vectorIndex] = DOWN;
			//Observable::getInstance().SendToObservers(MessageType::Key);
		}
		else if (!isKeyDown && (lastKeyState == DOWN))
		{
			keyState[vectorIndex] = TRIGGERED;
			//Observable::getInstance().SendToObservers(MessageType::Key);
		}
		else
		{
			keyState[vectorIndex] = RELEASE;
		}
	}

	for (char i = Key::NUM_0; i <= Key::NUM_9; i++)
	{
		int vectorIndex = i - Key::NUM_0 + Key::TOTAL_LETTERS;
		bool isKeyDown = (glfwGetKey(ptrWindow, i) == GLFW_PRESS);
		KeyState lastKeyState = keyState[vectorIndex];

		if (isKeyDown)
		{
			//if (lastKeyState != DOWN && PhysicsSystem::GetInstance()->GetStepByStep())
			//{
			//	PhysicsSystem::GetInstance()->SetisUpdated(false);
			//}
			keyState[vectorIndex] = DOWN;
			//Observable::getInstance().SendToObservers(MessageType::Key);
		}
		else if (!isKeyDown && (lastKeyState == DOWN))
		{
			keyState[vectorIndex] = TRIGGERED;
			//Observable::getInstance().SendToObservers(MessageType::Key);
		}
		else
		{
			keyState[vectorIndex] = RELEASE;
		}
	}

	for (int i = MouseButton::BUTTON_LEFT; i < TOTAL_BUTTONS; i++)
	{
		bool isMouseDown = (glfwGetMouseButton(ptrWindow, i) == GLFW_PRESS);
		KeyState lastMouseState = mouseState[i];
		if (isMouseDown)
		{
			mouseState[i] = DOWN;
		}
		else if (!isMouseDown && (lastMouseState == DOWN))
		{
			mouseState[i] = TRIGGERED;
		}
		else
		{
			mouseState[i] = RELEASE;
		}
	}
	//if (InputSystem::isKeyTriggered(InputSystem::key::NUM_0))
	//{
	//	bool mode = PhysicsSystem::GetInstance()->GetStepByStep();
	//	PhysicsSystem::GetInstance()->SetStepByStep(!mode);
	//}
}
