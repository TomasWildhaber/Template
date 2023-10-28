#pragma once
#include "Renderer/Buffer.h"

namespace Application
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* verticies, unsigned int size);
		~OpenGLVertexBuffer();

		virtual inline void Bind() const override;
		virtual inline void UnBind() const override;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* _indicies, uint32_t _count);
		~OpenGLIndexBuffer();

		virtual inline void Bind() const override;
		virtual inline void UnBind() const override;
	};
}