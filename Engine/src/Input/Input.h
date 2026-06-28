#pragma once
#include "Windows.h"
#include <array>
#include <vector>

struct GLFWwindow;

namespace Engine
{
	class Input
	{
	public:
		static void Initialize(GLFWwindow* window, bool useRawInput = true);
		static void OnMouseMove(LPARAM lparam);
		static void OnKeyDown(WPARAM vkey);
		static void OnKeyUp(WPARAM vkey);


		static void OnUpdate();

		static bool IsKeyDown(int vkey);
		static bool IsKeyPressed(int vkey);
		static bool IsKeyReleased(int vkey);

		static POINT GetMousePosition();
		static POINT GetMouseDelta();
		static int GetMouseDeltaX();
		static int GetMouseDeltaY();
		static void OnMouseButtonDown(int button);
		static void OnMouseButtonUp(int button);

		static bool IsMouseButtonDown(int button);
		static bool IsMouseButtonPressed(int button);
		static bool IsMouseButtonReleased(int button);

	private:
		static inline bool s_useRaw = false;

		static inline std::array<uint8_t, 256> s_keys = {};
		static inline std::array<uint8_t, 256> s_prevKeys = {};
		static inline std::array<uint8_t, 3> s_mouseButtons = {};
		static inline std::array<uint8_t, 3> s_prevmouseButtons = {};

		static inline LONG s_mouseX = 0, s_mouseY = 0;
		static inline LONG s_mouseDX = 0, s_mouseDY = 0;
		static inline LONG s_mouseLastX = 0, s_mouseLastY = 0;

	};
}