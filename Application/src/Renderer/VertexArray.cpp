#include "VertexArray.h"
#include "Platform/RenderAPIs/OpenGL/OpenGLVertexArray.h"
#include "Renderer.h"
#include "Debugging/Logger.h"

namespace Application
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::API)
		{
			case Renderer::APIs::None:
				Log("Cannot create Vertex array. No rendering API selected!");
				return nullptr;

			case Renderer::APIs::OpenGL:
				Log("Creating Vertex array!");
				return new OpenGLVertexArray();

			case Renderer::APIs::Vulkan:
				Log("Cannot create Vertex array. Vulkan is not supported yet!");
				return nullptr;

			case Renderer::APIs::DirectX:
				Log("Cannot create Vertex array. DirectX is not supported yet!");
				return nullptr;

			case Renderer::APIs::Metal:
				Log("Cannot create Vertex array. Metal is not supported yet!");
				return nullptr;

			default:
				Log("Cannot create Vertex array. Unkown rendering API!");
				return nullptr;
		}
	}
}