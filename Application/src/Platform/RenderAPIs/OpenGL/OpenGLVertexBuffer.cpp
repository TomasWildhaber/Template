#include "OpenGLVertexBuffer.h"
#include "glad/glad.h"

namespace Application
{
	void OpenGLVertexBuffer::Bind() const
	{
		glBindVertexArray(id);
	}

	void OpenGLVertexBuffer::UnBind() const
	{
		glBindVertexArray(0);
	}
}