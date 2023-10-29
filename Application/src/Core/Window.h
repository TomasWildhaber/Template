#pragma once
#include "Event/Event.h"
#include "glm/glm.hpp"

struct GLFWwindow;

namespace Application
{
	class Window
	{
	public:
		virtual ~Window() {}

		using EventCallbackFunction = std::function<void(Event&)>;

		virtual inline void OnUpdate() const = 0;
		virtual inline void OnRender() const = 0;

		virtual inline uint32_t GetWidth() const = 0;
		virtual inline uint32_t GetHeight() const = 0;
		virtual inline glm::vec2 GetCurrentResolution() const = 0;
		virtual inline void* GetNativeWindow() const = 0;

		virtual void SetEventCallback(const EventCallbackFunction& callback) = 0;
		virtual inline void SetVSync(bool Enabled) = 0;
		virtual inline bool IsVSync() const = 0;

		virtual inline void MaximizeWindow() const = 0;
		virtual inline void ShowWindow() const = 0;
		virtual inline void HideWindow() const = 0;

		struct WindowData {
			uint32_t width, height;
			EventCallbackFunction CallbackFunction;
		};

		WindowData data;

		static Window* Create(uint32_t width, uint32_t height, const char* title);
	};
}

#ifdef WINDOWS_PLATFORM
	#include "Platform/Platforms/Windows/WindowsWindow.h"
#endif