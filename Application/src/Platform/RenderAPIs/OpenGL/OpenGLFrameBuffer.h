#pragma once
#include "Renderer/FrameBuffer.h"

namespace Application
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const float& _width, const float& _height, uint32_t _samples);
		~OpenGLFrameBuffer();

		virtual inline void Bind() const override;
		virtual inline void UnBind() const override;

		virtual inline void Resize(const float& _width, const float& _height) override;
		virtual inline void Copy(FrameBuffer* framebuffer) override;
	private:
		virtual void Initialize(const float& _width, const float& _height, uint32_t _samples) override;
	};
}