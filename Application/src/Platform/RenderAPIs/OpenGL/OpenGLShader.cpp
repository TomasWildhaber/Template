#include "OpenGLShader.h"
#include "glad/glad.h"
#include "Debugging/Logger.h"
#include <fstream>
#include <string>
#include "glm/gtc/type_ptr.hpp"

namespace Application
{
	static uint32_t GetOpenGLShaderType(ShaderType& type)
	{
		switch (type)
		{
			case ShaderType::None:					return 0;
			case ShaderType::VertexShader:			return GL_VERTEX_SHADER;
			case ShaderType::GeometryShader:		return GL_GEOMETRY_SHADER;
			case ShaderType::FragmentShader:		return GL_FRAGMENT_SHADER;
		}

		Log("Invalid shader type!");
		return 0;
	}

	OpenGLShader::OpenGLShader()
	{
		id = glCreateProgram();
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(id);
		OpenGLShader::UnBind();
	}

	void OpenGLShader::AttachShader(const char* path, ShaderType type)
	{
		std::string source;
		{
			std::ifstream stream(path);
			std::string line;
			while (getline(stream, line))
				source += line + "\n";
			stream.close();
		}

		const char* src = source.c_str();
		uint32_t shaderId = glCreateShader(GetOpenGLShaderType(type));
		glShaderSource(shaderId, 1, &src, nullptr);
		glCompileShader(shaderId);

		int result;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
		if (!result)
		{
			int length;
			glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(shaderId, length, &length, message);
			std::string shaderType = type == ShaderType::VertexShader ? "vertex" : type == ShaderType::GeometryShader ? "geometry" : "fragment";
			std::string errorOutput = "Failed to compile " + shaderType + " shader";
			Log(errorOutput);
			Log(message);
			glDeleteShader(shaderId);
			return;
		}

		glAttachShader(id, shaderId);
		shaders.push_back(shaderId);
	}

	inline void OpenGLShader::LinkShaders()
	{
		glLinkProgram(id);
		glValidateProgram(id);

		for (uint32_t i = 0; i < shaders.size(); i++)
		{
			glDetachShader(id, shaders[i]);
			glDeleteShader(shaders[i]);
		}

		shaders.clear();
	}

	inline void OpenGLShader::Bind() const
	{
		glUseProgram(id);
	}

	inline void OpenGLShader::UnBind() const
	{
		glUseProgram(0);
	}

	inline const void OpenGLShader::SetInt1(const char* name, int& value) const
	{
		int location = glGetUniformLocation(id, name);
		glUniform1i(location, value);
	}

	inline const void OpenGLShader::SetInt2(const char* name, glm::vec2& value) const
	{
		int location = glGetUniformLocation(id, name);
		glUniform2i(location, value.x, value.y);
	}

	inline const void OpenGLShader::SetInt3(const char* name, glm::vec3& value) const
	{
		int location = glGetUniformLocation(id, name);
		glUniform3i(location, value.x, value.y, value.z);
	}

	inline const void OpenGLShader::SetInt4(const char* name, glm::vec4& value) const
	{
		int location = glGetUniformLocation(id, name);
		glUniform4i(location, value.x, value.y, value.z, value.w);
	}

	inline const void OpenGLShader::SetIntArray(const char* name, int* values, uint32_t count) const
	{
		int location = glGetUniformLocation(id, name);
		glUniform1iv(location, count, values);
	}

	inline const void OpenGLShader::SetFloat1(const char* name, float& value) const
	{
		int location = glGetUniformLocation(id, name);
		glUniform1f(location, value);
	}

	inline const void OpenGLShader::SetFloat2(const char* name, glm::vec2& value) const
	{
		int location = glGetUniformLocation(id, name);
		glUniform2f(location, value.x, value.y);
	}

	inline const void OpenGLShader::SetFloat3(const char* name, glm::vec3& value) const
	{
		int location = glGetUniformLocation(id, name);
		glUniform3f(location, value.x, value.y, value.z);
	}

	inline const void OpenGLShader::SetFloat4(const char* name, glm::vec4& value) const
	{
		int location = glGetUniformLocation(id, name);
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	inline const void OpenGLShader::SetMat3(const char* name, glm::mat3& value) const
	{
		int location = glGetUniformLocation(id, name);
		glUniformMatrix3fv(location, 1, false, glm::value_ptr(value));
	}

	inline const void OpenGLShader::SetMat4(const char* name, glm::mat4& value) const
	{
		int location = glGetUniformLocation(id, name);
		glUniformMatrix4fv(location, 1, false, glm::value_ptr(value));
	}
}