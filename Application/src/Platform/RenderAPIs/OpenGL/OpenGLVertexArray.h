#pragma once
#include "Renderer/VertexArray.h"

namespace Application
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		virtual inline void Bind() const override;
		virtual inline void UnBind() const override;

		virtual void AttachVertexBuffer(VertexBuffer& buffer, Shader* shader) override;
		virtual void AttachIndexBuffer(IndexBuffer& buffer) override;
	};
}