#include "OpenGLShader.h"
#include "glad/glad.h"
#include "Debugging/Logger.h"
#include <fstream>
#include <string>

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
}