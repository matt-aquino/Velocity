#pragma once
#include "Velocity/Renderer/Framebuffer.h"

namespace Velocity
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecs&);
		virtual ~OpenGLFramebuffer();

		void Invalidate();
		virtual void Bind() override;
		virtual void Unbind() override;
		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual uint32_t GetColorAttachmentID() const override { return m_ColorAttachment; }
		virtual const FramebufferSpecs& GetSpecs() const override { return m_Specs; }

	private:
		uint32_t m_RendererID = 0, m_ColorAttachment, m_DepthAttachment;
		FramebufferSpecs m_Specs;
	};
}