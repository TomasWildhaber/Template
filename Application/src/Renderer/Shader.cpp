#include "Shader.h"
#include "Platform/RenderAPIs/OpenGL/OpenGLShader.h"
#include "Renderer.h"
#include "Debugging/Logger.h"

namespace Application
{
	Shader* Shader::Create()
	{
		switch (Renderer::API)
		{
			case Renderer::APIs::None:
				Log("Cannot create Shader. No rendering API selected!");
				return nullptr;

			case Renderer::APIs::OpenGL:
				Log("Creating Shader!");
				return new OpenGLShader();

			case Renderer::APIs::Vulkan:
				Log("Cannot create Shader. Vulkan is not supported yet!");
				return nullptr;

			case Renderer::APIs::DirectX:
				Log("Cannot create Shader. DirectX is not supported yet!");
				return nullptr;

			case Renderer::APIs::Metal:
				Log("Cannot create Shader. Metal is not supported yet!");
				return nullptr;

			default:
				Log("Cannot create Shader. Unkown rendering API!");
				return nullptr;
		}
	}
}