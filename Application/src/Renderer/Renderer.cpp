#include "Renderer.h"
#include "Debugging/Logger.h"
#include "Platform/RenderAPIs/OpenGL/OpenGLRenderer.h"

namespace Application
{
	Renderer::APIs Renderer::API;

	Renderer* Renderer::Create()
	{
		switch (Renderer::API)
		{
			case Renderer::APIs::None:
				Log("No rendering API selected!");
				return nullptr;

			case Renderer::APIs::OpenGL:
				Log("OpenGL selected!");
				return new OpenGLRenderer();

			case Renderer::APIs::DirectX:
				Log("DirectX is not supported yet!");
				return nullptr;

			case Renderer::APIs::Vulkan:
				Log("Vulkan is not supported yet!");
				return nullptr;

			case Renderer::APIs::Metal:
				Log("Metal is not supported yet!");
				return nullptr;

			default:
				Log("Unkown rendering API!");
				return nullptr;
		}
	}
}