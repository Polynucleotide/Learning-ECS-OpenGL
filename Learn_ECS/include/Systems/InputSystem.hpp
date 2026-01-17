/*****************************************************************//**
 * @file   InputSystem.hpp
 * @brief Declares the input system for handling keyboard and mouse inputs.
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

#ifndef INPUT_SYSTEM_HPP
#define INPUT_SYSTEM_HPP

#include "GLFW/glfw3.h"
#include "Math/Vector2.hpp"
#include <vector>
#include <utility>

class InputSystem // handles key and mouse button states, while also tracking mouse position and updating input.
{
	public:
		static InputSystem& GetInstance()
		{
			static InputSystem instance;
			return instance;
		}

		InputSystem(InputSystem const&) = delete;
		InputSystem& operator=(InputSystem const&) = delete;

		enum Key // key codes for letters and numbers
		{
			A = GLFW_KEY_A,
			B,
			C,
			D,
			E,
			F,
			G,
			H,
			I,
			J,
			K,
			L,
			M,
			N,
			O,
			P,
			Q,
			R,
			S,
			T,
			U,
			V,
			W,
			X,
			Y,
			Z,
			TOTAL_LETTERS = 26,
			NUM_0 = GLFW_KEY_0,
			NUM_1,
			NUM_2,
			NUM_3,
			NUM_4,
			NUM_5,
			NUM_6,
			NUM_7,
			NUM_8,
			NUM_9,
			TOTAL_KEYS = 36
		};

		enum MouseButton // mouse button codes
		{
			BUTTON_LEFT = GLFW_MOUSE_BUTTON_LEFT,
			BUTTON_RIGHT,
			BUTTON_MIDDLE,
			TOTAL_BUTTONS = 3
		};

		enum KeyState // states for keys and mouse buttons
		{
			DOWN,
			TRIGGERED,
			RELEASE
		};

		/*!
		* @brief Checks if a specified key is currently pressed down.
		*
		* @param key - The key to check.
		* @return True if the key is pressed down, false otherwise.
		*//*______________________________________________________________*/
		static bool KeyDown(Key key);

		/*!
		* @brief Checks if a specified key has just been pressed.
		*
		* @param key - The key to check.
		* @return True if the key was just pressed, false otherwise.
		*//*______________________________________________________________*/
		static bool KeyTriggered(Key key);

		/*!
		* @brief Checks if a specified mouse button is currently pressed down.
		*
		* @param mouseButton - The mouse button to check.
		* @return True if the mouse button is pressed down, false otherwise.
		 *//*______________________________________________________________*/
		static bool MouseDown(MouseButton mouseButton);

		/*!
		* @brief Checks if a specified mouse button has just been clicked.
		*
		* @param mouseButton - The mouse button to check.
		* @return True if the mouse button was just clicked, false otherwise.
		 *//*______________________________________________________________*/
		static bool MouseClick(MouseButton mouseButton);

		/*!
		* @brief Gets the current mouse position.
		*
		* @return Current mouse position as Vector2
		*//*______________________________________________________________*/
		static Vector2 GetMousePosition();

		/*!
		* @brief Gets the difference between the current and previous mouse position.
		* 
		* @return Difference between mouse positions from the previous frame as Vector2
		*//*______________________________________________________________*/
		static Vector2 GetMousePositionDelta();

		/*!
		* @brief Updates the input system each frame, tracking key states and mouse position.
		 *//*______________________________________________________________*/
		void Update();

	private:
		InputSystem() = default;
		static std::vector<KeyState> keyState; // vector to store state of all keys
		static std::vector<KeyState> mouseState; // vector to store state of all mouse buttons
		static std::pair<double, double> mousePos; // stores current mouse pos in terms of x and y
		static std::pair<double, double> previousMousePos; // stores previous mouse pos in terms of x and y
};

#endif // !INPUT_SYSTEM_HPP
