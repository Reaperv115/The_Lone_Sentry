#include "gepch.h"
#include "Input.h"
#include <Windows.h>
#include <GLFW/glfw3.h>

void Engine::Input::Initialize(GLFWwindow* window, bool useRawInput /*= true*/)
{

    // store provided handle/flags in static members
    s_useRaw = useRawInput;

    double mx, my;
	glfwGetCursorPos(window, &mx, &my);
	s_mouseLastX = mx;
	s_mouseLastY = my;
	s_mouseX = mx;
	s_mouseY = my;
	
	glfwSetKeyCallback(window, [](GLFWwindow*, int key, int scancode, int action, int mods)
		{
			if (key < 0 || key >= 512) return;
			if (action == GLFW_PRESS || action == GLFW_REPEAT) Input::OnKeyDown((WPARAM)key);
			else if (action == GLFW_RELEASE) Input::OnKeyUp((WPARAM)key);
		});

	glfwSetCursorPosCallback(window, [](GLFWwindow*, double xpos, double ypos) {
		LPARAM lparam = MAKELPARAM((int)std::lround(xpos), (int)std::lround(ypos));
		Input::OnMouseMove(lparam);
		});

	glfwSetMouseButtonCallback(window, [](GLFWwindow*, int button, int action, int mods)
		{
			int b = -1;
			if (button == GLFW_MOUSE_BUTTON_LEFT) b = 0;
			else if (button == GLFW_MOUSE_BUTTON_RIGHT) b = 1;
			else if (button == GLFW_MOUSE_BUTTON_MIDDLE) b = 2;
			if (b < 0) return;
			if (action == GLFW_PRESS) Input::OnMouseButtonDown(b);
			else if (action == GLFW_RELEASE) Input::OnMouseButtonUp(b);
		});
}


void Engine::Input::OnMouseMove(LPARAM lparam)
{
	int x = GET_X_LPARAM(lparam);
	int y = GET_Y_LPARAM(lparam);


	s_mouseDX += (x - s_mouseLastX);
	s_mouseDY += (y - s_mouseLastY);


	s_mouseLastX = x;
	s_mouseLastY = y;
	s_mouseX = x;
	s_mouseY = y;
}

void Engine::Input::OnKeyDown(WPARAM vkey)
{
	if (vkey < 256) s_keys[static_cast<size_t>(vkey)] = 1;
}

void Engine::Input::OnKeyUp(WPARAM vkey)
{
	if (vkey < 256) s_keys[static_cast<size_t>(vkey)] = 0;
}

void Engine::Input::OnUpdate()
{
	s_prevKeys = s_keys;
	s_prevmouseButtons = s_mouseButtons;

	s_mouseDX = 0;
	s_mouseDY = 0;
}

bool Engine::Input::IsKeyDown(int vkey)
{
	if (vkey < 0 || vkey >= 256) return false;
	return s_keys[vkey] != 0;
}

bool Engine::Input::IsKeyPressed(int vkey)
{
	if (vkey < 0 || vkey >= 256) return false;
	return s_keys[vkey] != 0 && s_prevKeys[vkey] == 0;
}

bool Engine::Input::IsKeyReleased(int vkey)
{
	if (vkey < 0 || vkey >= 256) return false;
	return s_keys[vkey] == 0 && s_prevKeys[vkey] != 0;
}

POINT Engine::Input::GetMousePosition()
{
	return POINT{ s_mouseX, s_mouseY };
}


POINT Engine::Input::GetMouseDelta()
{
	return POINT{ s_mouseDX, s_mouseDY };
}

int Engine::Input::GetMouseDeltaX()
{
	return s_mouseDX;
}

int Engine::Input::GetMouseDeltaY()
{
	return s_mouseDY;
}

void Engine::Input::OnMouseButtonDown(int button)
{
	if (button >= 0 && button < 3) s_mouseButtons[button] = 1;
}

void Engine::Input::OnMouseButtonUp(int button)
{
	if (button >= 0 && button < 3) s_mouseButtons[button] = 0;
}

bool Engine::Input::IsMouseButtonDown(int button)
{
	if (button < 0 || button >= 3) return false;
	return s_mouseButtons[button] != 0;
}

bool Engine::Input::IsMouseButtonPressed(int button)
{
	if (button < 0 || button >= 3) return false;
	return s_mouseButtons[button] != 0 && s_prevmouseButtons[button] == 0;
}

bool Engine::Input::IsMouseButtonReleased(int button)
{
	if (button < 0 || button >= 3) return false;
	return s_prevmouseButtons[button] == 1 || s_mouseButtons[button] == 0;
}

