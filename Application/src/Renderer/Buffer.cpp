#include "Buffer.h"
#include "Platform/RenderAPIs/OpenGL/OpenGLBuffer.h"
#include "Renderer.h"
#include "Debugging/Logger.h"

namespace Application
{
	VertexBuffer* VertexBuffer::Create(float* verticies, uint32_t size)
	{
		switch (Renderer::API)
		{
		case Renderer::APIs::None:
			Log("Cannot create Vertex buffer. No rendering API selected!");
			return nullptr;

		case Renderer::APIs::OpenGL:
			Log("Creating Vertex buffer!");
			return new OpenGLVertexBuffer(verticies, size);

		case Renderer::APIs::Vulkan:
			Log("Cannot create Vertex buffer. Vulkan is not supported yet!");
			return nullptr;

		case Renderer::APIs::DirectX:
			Log("Cannot create Vertex buffer. DirectX is not supported yet!");
			return nullptr;

		case Renderer::APIs::Metal:
			Log("Cannot create Vertex buffer. Metal is not supported yet!");
			return nullptr;

		default:
			Log("Cannot create Vertex buffer. Unkown rendering API!");
			return nullptr;
		}
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* _indicies, uint32_t _count)
	{
		switch (Renderer::API)
		{
		case Renderer::APIs::None:
			Log("Cannot create Index buffer. No rendering API selected!");
			return nullptr;

		case Renderer::APIs::OpenGL:
			Log("Creating Index buffer!");
			return new OpenGLIndexBuffer(_indicies, _count);

		case Renderer::APIs::Vulkan:
			Log("Cannot create Index buffer. Vulkan is not supported yet!");
			return nullptr;

		case Renderer::APIs::DirectX:
			Log("Cannot create Index buffer. DirectX is not supported yet!");
			return nullptr;

		case Renderer::APIs::Metal:
			Log("Cannot create Index buffer. Metal is not supported yet!");
			return nullptr;

		default:
			Log("Cannot create Index buffer. Unkown rendering API!");
			return nullptr;
		}
	}
}