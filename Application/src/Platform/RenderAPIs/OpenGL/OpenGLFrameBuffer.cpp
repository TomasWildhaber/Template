#include "OpenGLFrameBuffer.h"
#include "glad/glad.h"
#include "Debugging/Logger.h"

namespace Application
{
	OpenGLFrameBuffer::OpenGLFrameBuffer(const float& _width, const float& _height, uint32_t _samples)
	{
		samples = _samples;
		multisampled = multisampled > 1 ? true : false;
		OpenGLFrameBuffer::Initialize(_width, _height, _samples);
	}

	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glDeleteTextures(1, &textureId);
		glDeleteRenderbuffers(1, &renderId);
		glDeleteFramebuffers(1, &id);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	inline void OpenGLFrameBuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, id);
	}

	inline void OpenGLFrameBuffer::UnBind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	inline void OpenGLFrameBuffer::Resize(const float& _width, const float& _height)
	{
		OpenGLFrameBuffer::Initialize(_width, _height, samples);
	}

	inline void OpenGLFrameBuffer::Copy(FrameBuffer* framebuffer)
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer->GetId());
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, id);
		glBlitFramebuffer(0, 0, framebuffer->GetWidth(), framebuffer->GetHeight(), 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	}

	void OpenGLFrameBuffer::Initialize(const float& _width, const float& _height, uint32_t _samples)
	{
		if (id)
		{
			glDeleteTextures(1, &textureId);
			glDeleteRenderbuffers(1, &renderId);
			glDeleteFramebuffers(1, &id);
			Log("Framebuffer resized!");
		}

		width = _width;
		height = _height;

		glGenFramebuffers(1, &id);
		glBindFramebuffer(GL_FRAMEBUFFER, id);
		glGenTextures(1, &textureId);

		if (multisampled)
		{
			glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, textureId);
			glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGB, width, height, GL_TRUE);
			glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, textureId, 0);
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, textureId);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId, 0);
		}
		
		glGenRenderbuffers(1, &renderId);
		glBindRenderbuffer(GL_RENDERBUFFER, renderId);
		if (multisampled)
			glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_DEPTH24_STENCIL8, width, height);
		else
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderId);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			Log("Framebuffer is not complete!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		if (multisampled)
			glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
		else
			glBindTexture(GL_TEXTURE_2D, 0);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}
}