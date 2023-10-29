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

		virtual inline const void SetInt1(const char* name, int& value) const override;
		virtual inline const void SetInt2(const char* name, glm::vec2& value) const override;
		virtual inline const void SetInt3(const char* name, glm::vec3& value) const override;
		virtual inline const void SetInt4(const char* name, glm::vec4& value) const override;
		virtual inline const void SetIntArray(const char* name, int* values, uint32_t count) const override;
		virtual inline const void SetFloat1(const char* name, float& value) const override;
		virtual inline const void SetFloat2(const char* name, glm::vec2& value) const override;
		virtual inline const void SetFloat3(const char* name, glm::vec3& value) const override;
		virtual inline const void SetFloat4(const char* name, glm::vec4& value) const override;
		virtual inline const void SetMat3(const char* name, glm::mat3& value) const override;
		virtual inline const void SetMat4(const char* name, glm::mat4& value) const override;

		virtual void AttachShader(const char* path, ShaderType type) override;
		virtual inline void LinkShaders() override;
	};
}