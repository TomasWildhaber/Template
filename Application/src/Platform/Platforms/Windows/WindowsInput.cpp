#ifdef WINDOWS_PLATFORM

#include "Core/Input.h"
#include "Core/Application.h"
#include "GLFW/glfw3.h"

namespace Application
{
	bool Input::IsKeyPressed(int keyCode)
	{
		GLFWwindow* window = Application::Get().GetWindow().GetGLWindow();
		int state = glfwGetKey(window, keyCode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(int button)
	{
		GLFWwindow* window = Application::Get().GetWindow().GetGLWindow();
		int state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	glm::vec2 Input::GetMousePosition()
	{
		GLFWwindow* window = Application::Get().GetWindow().GetGLWindow();
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return { (float)x, (float)y };
	}

	float Input::GetMouseX()
	{
		return GetMousePosition().x;
	}

	float Input::GetMouseY()
	{
		return GetMousePosition().y;
	}
}

#endif