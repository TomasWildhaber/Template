#pragma once

#include "Core/Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Application
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(uint32_t width, uint32_t height, const char* title);
		~WindowsWindow();

		virtual inline uint32_t GetWidth() const override { return data.width; }
		virtual inline uint32_t GetHeight() const override { return data.height; }
		virtual inline glm::vec2 GetCurrentResolution() const override { return { data.width, data.height }; }
		virtual inline void* GetNativeWindow() const override { return window; }

		virtual inline void OnUpdate() const override;
		virtual inline void OnRender() const override;
		virtual void SetEventCallback(const EventCallbackFunction& callback) override { data.CallbackFunction = callback; }

		virtual inline void SetVSync(bool Enabled) override { glfwSwapInterval(Enabled); vsync = Enabled; }
		virtual inline bool IsVSync() const override { return vsync; }

		virtual inline void MaximizeWindow() const override { glfwMaximizeWindow(window); }
		virtual inline void ShowWindow() const override { glfwShowWindow(window); }
		virtual inline void HideWindow() const override { glfwHideWindow(window); }
	private:
		inline void const initGL();
		inline void const initGlad();
		inline void setCallbacks();

		GLFWwindow* window;
		bool vsync;
	};
}