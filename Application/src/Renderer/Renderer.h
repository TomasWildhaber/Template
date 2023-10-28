#pragma once
#include "VertexArray.h"
#include "Shader.h"

namespace Application
{
	class Renderer
	{
	public:
		virtual ~Renderer() {}

		static enum class APIs
		{
			None,
			OpenGL,
			Vulkan,
			DirectX,
			Metal,
		};

		static APIs API;
		static Renderer* Create();

		virtual void OnWindowResize(float width, float height) const = 0;
		virtual void DrawArrays(const VertexArray* vao, const Shader* shader) const = 0;
		virtual void DrawElements(const VertexArray* vao, const Shader* shader) const = 0;
		virtual void Clear() const = 0;
	};
}