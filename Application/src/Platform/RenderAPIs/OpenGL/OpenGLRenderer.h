#pragma once
#include "Renderer/Renderer.h"

namespace Application
{
	class OpenGLRenderer : public Renderer
	{
		virtual void OnWindowResize(float width, float height) const override;
		virtual void DrawArrays() const override;
		virtual void DrawElements() const override;
		virtual void Clear() const override;
	};
}