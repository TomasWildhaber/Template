#pragma once
#include "Platform/RenderAPIs/OpenGL/OpenGLBuffer.h"
#include "Renderer/Shader.h"

namespace Application
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual inline void Bind() const = 0;
		virtual inline void UnBind() const = 0;

		virtual void AttachVertexBuffer(VertexBuffer& buffer, Shader* shader) = 0;
		virtual void AttachIndexBuffer(IndexBuffer& buffer) = 0;
		inline const IndexBuffer* GetIndexBuffer() const { return indexBuffer; }

		static VertexArray* Create();
	protected:
		unsigned int id;

		IndexBuffer* indexBuffer;
		std::vector<VertexBuffer*> vertexBuffers;
	};
}