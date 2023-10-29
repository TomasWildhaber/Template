#include "FrameBuffer.h"
#include "Platform/RenderAPIs/OpenGL/OpenGLFrameBuffer.h"
#include "Renderer.h"
#include "Debugging/Logger.h"

namespace Application
{
	FrameBuffer* FrameBuffer::Create(float _width, float _height, uint32_t _samples)
	{
		switch (Renderer::API)
		{
			case Renderer::APIs::None:
				Log("Cannot create Framebuffer. No rendering API selected!");
				return nullptr;

			case Renderer::APIs::OpenGL:
				Log("Creating Framebuffer!");
				return new OpenGLFrameBuffer(_width, _height, _samples);

			case Renderer::APIs::Vulkan:
				Log("Cannot create Framebuffer. Vulkan is not supported yet!");
				return nullptr;

			case Renderer::APIs::DirectX:
				Log("Cannot create Framebuffer. DirectX is not supported yet!");
				return nullptr;

			case Renderer::APIs::Metal:
				Log("Cannot create Framebuffer. Metal is not supported yet!");
				return nullptr;

			default:
				Log("Cannot create Framebuffer. Unkown rendering API!");
				return nullptr;
		}
	}
}