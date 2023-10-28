#pragma once
#include <cstdint>
#include <vector>

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

		virtual void AttachShader(const char* path, ShaderType type) = 0;
		virtual inline void LinkShaders() = 0;

		static Shader* Create();
	protected:
		uint32_t id;
		std::vector<uint32_t> shaders;
	};
}