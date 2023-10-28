#include "OpenGLRenderer.h"
#include "glad/glad.h"

namespace Application
{
	void OpenGLRenderer::OnWindowResize(float width, float height) const
	{
		glViewport(0, 0, width, height);
	}

	void OpenGLRenderer::DrawArrays(const VertexArray* vao, const Shader* shader) const
	{
		vao->Bind();
		shader->Bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	void OpenGLRenderer::DrawElements(const VertexArray* vao, const Shader* shader) const
	{
		vao->Bind();
		shader->Bind();
		glDrawElements(GL_TRIANGLES, vao->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
	}

	void OpenGLRenderer::Clear() const
	{
		glClearColor(0.4f, 0.4f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}