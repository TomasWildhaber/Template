#include "OpenGLRenderer.h"
#include "glad/glad.h"

namespace Application
{
	void OpenGLRenderer::OnWindowResize(float width, float height) const
	{
		glViewport(0, 0, width, height);
	}

	void OpenGLRenderer::DrawArrays() const
	{

	}

	void OpenGLRenderer::DrawElements() const
	{

	}

	void OpenGLRenderer::Clear() const
	{
		glClearColor(0.4f, 0.4f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}