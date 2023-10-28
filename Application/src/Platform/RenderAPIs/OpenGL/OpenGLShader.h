#pragma once
#include "Renderer/Shader.h"

namespace Application
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader();
		~OpenGLShader();

		virtual inline void Bind() const override;
		virtual inline void UnBind() const override;

		virtual inline const uint32_t& GetId() override { return id; };

		virtual void AttachShader(const char* path, ShaderType type) override;
		virtual inline void LinkShaders() override;
	};
}