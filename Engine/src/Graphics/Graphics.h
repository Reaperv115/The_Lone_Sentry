#pragma once
#include "OpenGLContext.h"
#include "Core.h"
#include <string>

struct GLFWwindow;
struct GLFWmonitor;

namespace Engine
{
	class Graphics
	{
	public:
		Graphics(float width, float height, const std::string& windowname);
		~Graphics() = default;

		void InitializeGraphics();
		void SetAPIFlags();

		inline void SwapBuffers() { windowContext->SwapBuffers(); }

		inline GLFWwindow* GetNativeWindow() const { return _window; }
		inline Unique<OpenGLContext>& GetContext() { return windowContext; }

		bool ShouldWindowClose() const;
	private:
		GLFWwindow* _window = nullptr;
		GLFWmonitor* monitor = nullptr;

		Unique<OpenGLContext> windowContext;

		float windowWidth, windowHeight;
		std::string windowTitle;
	};
}