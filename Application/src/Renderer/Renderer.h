#pragma once

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
			Mattel,
		};

		static APIs API;
		static Renderer* Create();

		virtual void OnWindowResize(float width, float height) const = 0;
		virtual void DrawArrays() const = 0;
		virtual void DrawElements() const = 0;
		virtual void Clear() const = 0;
	};
}