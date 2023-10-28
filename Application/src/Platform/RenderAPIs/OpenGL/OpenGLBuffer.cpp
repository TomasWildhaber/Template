#include "OpenGLBuffer.h"
#include "glad/glad.h"

namespace Application
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* verticies, unsigned int size)
	{
		glGenBuffers(1, &id);
		OpenGLVertexBuffer::Bind();
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), verticies, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &id);
		OpenGLVertexBuffer::UnBind();
	}

	inline void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}

	inline void OpenGLVertexBuffer::UnBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* _indicies, uint32_t _count) : IndexBuffer(_indicies, _count)
	{
		glGenBuffers(1, &id);
		OpenGLIndexBuffer::Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indicies, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &id);
		OpenGLIndexBuffer::UnBind();
	}

	inline void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	}

	inline void OpenGLIndexBuffer::UnBind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}