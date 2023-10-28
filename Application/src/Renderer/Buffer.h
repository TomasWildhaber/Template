#pragma once
#include <vector>
#include "Debugging/Logger.h"

namespace Application
{
	enum class BufferElementType
	{
		None,
		Bool,
		Float, Float2, Float3, Float4,
		Int, Int2, Int3, Int4,
	};

	struct BufferElement
	{
		const char* Name;
		BufferElementType Type;
		uint32_t Size;
		bool Normalized;

		static uint32_t GetElementTypeSize(BufferElementType type)
		{
			switch (type)
			{
				case BufferElementType::None:			return 0;
				case BufferElementType::Bool:			return 1;
				case BufferElementType::Float:			return 4;
				case BufferElementType::Float2:			return 4 * 2;
				case BufferElementType::Float3:			return 4 * 3;
				case BufferElementType::Float4:			return 4 * 4;
				case BufferElementType::Int:			return 4;
				case BufferElementType::Int2:			return 4 * 2;
				case BufferElementType::Int3:			return 4 * 3;
				case BufferElementType::Int4:			return 4 * 4;
			}

			Log("Invalid buffer element type!");
			return 0;
		}

		static uint32_t GetComponentCount(BufferElementType type)
		{
			switch (type)
			{
				case BufferElementType::None:			return 0;
				case BufferElementType::Bool:			return 1;
				case BufferElementType::Float:			return 4;
				case BufferElementType::Float2:			return 2;
				case BufferElementType::Float3:			return 3;
				case BufferElementType::Float4:			return 4;
				case BufferElementType::Int:			return 1;
				case BufferElementType::Int2:			return 2;
				case BufferElementType::Int3:			return 3;
				case BufferElementType::Int4:			return 4;
			}

			Log("Invalid buffer element type!");
			return 0;
		}

		BufferElement(BufferElementType type, const char* name, bool normalized = false) : Name(name), Type(type), Normalized(normalized), Size(BufferElement::GetElementTypeSize(type)) {}
	};

	class VertexBufferLayout
	{
	public:
		VertexBufferLayout() {}
		VertexBufferLayout(const std::initializer_list<BufferElement>& element) : elements(element)
		{
			for (const BufferElement& element : elements)
				stride += BufferElement::GetElementTypeSize(element.Type);
		}

		inline const std::vector<BufferElement>& GetElements() const { return elements; }
		inline const uint32_t GetStride() const { return stride; }
	private:
		std::vector<BufferElement> elements;
		uint32_t stride = 0;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual inline void Bind() const = 0;
		virtual inline void UnBind() const = 0;

		inline const VertexBufferLayout& GetLayout() const { return layout; }
		inline const void SetLayout(const VertexBufferLayout _layout) { layout = _layout; }

		static VertexBuffer* Create(float* verticies, uint32_t size);
	protected:
		VertexBufferLayout layout;
		uint32_t id;
	};

	class IndexBuffer
	{
	public:
		IndexBuffer(uint32_t* _indicies, uint32_t _count) : indicies(_indicies), count(_count) {}
		virtual ~IndexBuffer() {}

		virtual inline void Bind() const = 0;
		virtual inline void UnBind() const = 0;

		inline const uint32_t& GetCount() const { return count; }

		static IndexBuffer* Create(uint32_t* _indicies, uint32_t _count);
	protected:
		uint32_t id;
		uint32_t count;
		uint32_t* indicies;
	};
}