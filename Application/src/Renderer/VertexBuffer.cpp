#include "VertexBuffer.h"
#include "Renderer.h"
#include "Platform/RenderAPIs/OpenGL/OpenGLVertexBuffer.h"
#include "Debugging/Logger.h"

namespace Application
{
	VertexBuffer* VertexBuffer::Create(float* veticies, unsigned int size)
	{
		switch (Renderer::API)
		{
			case Renderer::APIs::None:
				Log("Cannot create Vertex buffer. No rendering API selected!");
				return nullptr;

			case Renderer::APIs::OpenGL:
				Log("Creating vertex buffer!");
				return new OpenGLVertexBuffer();

			case Renderer::APIs::DirectX:
				Log("Cannot create Vertex buffer. DirectX is not supported yet!");
				return nullptr;

			case Renderer::APIs::Vulkan:
				Log("Cannot create Vertex buffer. Vulkan is not supported yet!");
				return nullptr;

			case Renderer::APIs::Mattel:
				Log("Cannot create Vertex buffer. Mattel is not supported yet!");
				return nullptr;

			default:
				Log("Cannot create Vertex buffer. Unkown rendering API!");
				return nullptr;
		}
	}
}