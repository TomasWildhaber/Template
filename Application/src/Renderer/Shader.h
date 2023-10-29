#pragma once
#include <cstdint>
#include <vector>
#include "glm/glm.hpp"

namespace Application
{
	enum class ShaderDataType
	{
		None,
		Bool,
		Float, Float2, Float4,
		Mat3, Mat4,
		Int, Int2, Int3, Int4,
		Uniform1f, Uniform2f, Uniform3f, Uniform4f
	};

	enum class ShaderType
	{
		None,
		VertexShader, GeometryShader, FragmentShader
	};

	class Shader
	{
	public:
		virtual ~Shader() {}

		virtual inline void Bind() const = 0;
		virtual inline void UnBind() const = 0;

		virtual inline const uint32_t& GetId() = 0;

		virtual inline const void SetInt1(const char* name, int& value) const = 0;
		virtual inline const void SetInt2(const char* name, glm::vec2& value) const = 0;
		virtual inline const void SetInt3(const char* name, glm::vec3& value) const = 0;
		virtual inline const void SetInt4(const char* name, glm::vec4& value) const = 0;
		virtual inline const void SetIntArray(const char* name, int* values, uint32_t count) const = 0;
		virtual inline const void SetFloat1(const char* name, float& value) const = 0;
		virtual inline const void SetFloat2(const char* name, glm::vec2& value) const = 0;
		virtual inline const void SetFloat3(const char* name, glm::vec3& value) const = 0;
		virtual inline const void SetFloat4(const char* name, glm::vec4& value) const = 0;
		virtual inline const void SetMat3(const char* name, glm::mat3& value) const = 0;
		virtual inline const void SetMat4(const char* name, glm::mat4& value) const = 0;

		virtual void AttachShader(const char* path, ShaderType type) = 0;
		virtual inline void LinkShaders() = 0;

		static Shader* Create();
	protected:
		uint32_t id;
		std::vector<uint32_t> shaders;
	};
}