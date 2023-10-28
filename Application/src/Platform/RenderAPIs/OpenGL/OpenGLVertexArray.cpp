#include "Platform/RenderAPIs/OpenGL/OpenGLVertexArray.h"
#include "Debugging/OpenGLLogger.h"
#include "glad/glad.h"

namespace Application
{
	static GLenum GetOpenGLElementType(BufferElementType type)
	{
		switch (type)
		{
			case BufferElementType::None:			return 0;
			case BufferElementType::Bool:			return GL_BOOL;
			case BufferElementType::Float:			return GL_FLOAT;
			case BufferElementType::Float2:			return GL_FLOAT;
			case BufferElementType::Float3:			return GL_FLOAT;
			case BufferElementType::Float4:			return GL_FLOAT;
			case BufferElementType::Int:			return GL_UNSIGNED_INT;
			case BufferElementType::Int2:			return GL_UNSIGNED_INT;
			case BufferElementType::Int3:			return GL_UNSIGNED_INT;
			case BufferElementType::Int4:			return GL_UNSIGNED_INT;
		}

		Log("Invalid buffer element type!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &id);
		OpenGLVertexArray::Bind();
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &id);
		OpenGLVertexArray::UnBind();
	}

	inline void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(id);
	}

	inline void OpenGLVertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AttachVertexBuffer(VertexBuffer& buffer, Shader* shader)
	{
		OpenGLVertexArray::Bind();
		buffer.Bind();
		const VertexBufferLayout& layout = buffer.GetLayout();

		uint32_t offset = 0;
		for (const BufferElement& element : layout.GetElements())
		{
			uint32_t location = glGetAttribLocation(shader->GetId(), element.Name);
			glVertexAttribPointer(location, BufferElement::GetComponentCount(element.Type), GetOpenGLElementType(element.Type), element.Normalized, layout.GetStride(), (const void*)offset);
			glEnableVertexAttribArray(location);
			offset += BufferElement::GetElementTypeSize(element.Type);
		}

		vertexBuffers.push_back(&buffer);
	}

	void OpenGLVertexArray::AttachIndexBuffer(IndexBuffer& buffer)
	{
		OpenGLVertexArray::Bind();
		buffer.Bind();

		indexBuffer = &buffer;
	}
}