#pragma once
#include "Renderer/VertexBuffer.h"

namespace Application
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
		virtual void Bind() const override;
		virtual void UnBind() const override;
	};
}