#pragma once
#include <cstdint>

namespace Application
{
	class FrameBuffer
	{
	public:
		virtual ~FrameBuffer() {}

		virtual inline void Bind() const = 0;
		virtual inline void UnBind() const = 0;

		virtual inline const uint32_t& GetId() { return id; }
		virtual inline const uint32_t& GetTextureId() const { return textureId; }
		virtual inline const float& GetWidth() const { return width; }
		virtual inline const float& GetHeight() const { return height; }

		virtual inline void Resize(const float& _width, const float& _height) = 0;
		virtual inline void Copy(FrameBuffer* framebuffer) = 0;

		static FrameBuffer* Create(float _width, float _height, uint32_t _samples);
	protected:
		virtual void Initialize(const float& _width, const float& _height, uint32_t _samples) = 0;

		uint32_t id = 0;
		uint32_t renderId;
		uint32_t textureId;
		uint32_t samples;

		float width;
		float height;

		bool multisampled;
	};
}