#ifdef WINDOWS_PLATFORM

#include "WindowsWindow.h"
#include "Core/Input.h"
#include "Event/Events.h"
#include "Renderer/Time.h"
#include "Debugging/Logger.h"
#include "Renderer/Renderer.h"

namespace Application
{
	static bool glInitialized;

	float Time::currentFrame = 0.0f;
	float Time::deltaTime = 0.0f;
	float Time::lastFrame = 0.0f;

	Window* Window::Create(uint32_t width, uint32_t height, const char* title)
	{
		return new WindowsWindow(width, height, title);
	}

	WindowsWindow::WindowsWindow(uint32_t width, uint32_t height, const char* title)
	{
		data.width = width;
		data.height = height;

		if (!glInitialized)
		{
			Renderer::API = Renderer::APIs::OpenGL;

			initGL();
			glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
			window = glfwCreateWindow(data.width, data.height, title, nullptr, nullptr);
			glfwMakeContextCurrent(window);
			initGlad();
			setCallbacks();
		}

		glfwSetWindowUserPointer(window, &data);
		SetVSync(true);
	}

	WindowsWindow::~WindowsWindow()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	inline void const WindowsWindow::initGL()
	{
		if (!glfwInit()) {
			Log("Failed to initialize glfw!");
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	inline void const WindowsWindow::initGlad()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			Log("Failed to initialize glad!");
			delete this;
			return;
		}

		glEnable(GL_DEPTH_TEST);
		glInitialized = true;
	}

	inline void WindowsWindow::setCallbacks()
	{
		glfwSetErrorCallback([](int error, const char* description) {
			std::cout << "GLFW error: " << error << ", " << description << std::endl;
		});

		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
			WindowData& _data = *(WindowData*)glfwGetWindowUserPointer(window);
			_data.width = width;
			_data.height = height;

			WindowResizedEvent event(width, height);
			_data.CallbackFunction(event);
		});

		glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
			WindowData& _data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowClosedEvent event;
			_data.CallbackFunction(event);
		});

		glfwSetWindowPosCallback(window, [](GLFWwindow* window, int x, int y) {
			WindowData& _data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowMovedEvent event(x, y);
			_data.CallbackFunction(event);
		});

		glfwSetWindowFocusCallback(window, [](GLFWwindow* window, int focused) {
			WindowData& _data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowFocusedEvent event(focused);
			_data.CallbackFunction(event);
		});

		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& _data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					_data.CallbackFunction(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					_data.CallbackFunction(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					_data.CallbackFunction(event);
					break;
				}
			}
		});

		glfwSetCharCallback(window, [](GLFWwindow* window, uint32_t keyChar) {
			WindowData& _data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(keyChar);
			_data.CallbackFunction(event);
		});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& _data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					_data.CallbackFunction(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					_data.CallbackFunction(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
			WindowData& _data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event((float)xoffset, (float)yoffset);
			_data.CallbackFunction(event);
		});

		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos) {
			WindowData& _data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event((float)xPos, (float)yPos);
			_data.CallbackFunction(event);
		});
	}

	inline void WindowsWindow::OnUpdate() const
	{
		glfwPollEvents();

		Time::currentFrame = glfwGetTime();
		Time::deltaTime = Time::currentFrame - Time::lastFrame;
		Time::lastFrame = Time::currentFrame;
	}

	inline void WindowsWindow::OnRender() const
	{
		glfwSwapBuffers(window);
	}
}

#endif