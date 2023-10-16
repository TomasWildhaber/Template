#pragma once

namespace Application
{
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		static VertexBuffer* Create(float* verticies, unsigned int size);
	protected:
		unsigned int id;
	};
}