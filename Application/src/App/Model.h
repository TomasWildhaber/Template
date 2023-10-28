#pragma once
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"

namespace Application
{
	class Model
	{
	public:
		Model()
		{
			vertexBuffer = VertexBuffer::Create(verticies, 12);
			VertexBufferLayout layout({ { BufferElementType::Float3, "position" } });
			vertexBuffer->SetLayout(layout);

			indexBuffer = IndexBuffer::Create(indicies, 6);

			shader = Shader::Create();
			shader->AttachShader("Resources/Shaders/VertexShader.glsl", ShaderType::VertexShader);
			shader->AttachShader("Resources/Shaders/FragmentShader.glsl", ShaderType::FragmentShader);
			shader->LinkShaders();

			array = VertexArray::Create();
			array->AttachVertexBuffer(*vertexBuffer, shader);
			array->AttachIndexBuffer(*indexBuffer);
		}

		~Model()
		{
			delete vertexBuffer;
			delete indexBuffer;
			delete array;
			delete shader;
		}

		inline const Shader* GetShaders() { return shader; }
		inline const VertexArray* GetVertexArray() { return array; }
	private:
		VertexBuffer* vertexBuffer;
		IndexBuffer* indexBuffer;
		VertexArray* array;
		Shader* shader;

		float verticies[12] =
		{
			-0.5f, 0.5f, 0.0f,
			0.5f, 0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
		};

		uint32_t indicies[6] =
		{
			0, 1, 2,
			0, 3, 2,
		};
	};
}