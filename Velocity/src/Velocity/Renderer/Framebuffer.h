#pragma once

#include "Velocity/Core/Core.h"

namespace Velocity
{
	struct FramebufferSpecs
	{
		uint32_t Width, Height;
		uint32_t Samples = 1;
		bool SwapChainTarget = false; // decides whether we render to the screen, or a specific target
	};


	class Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;

		virtual const FramebufferSpecs& GetSpecs() const = 0;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual uint32_t GetColorAttachmentID() const = 0;

		static Ref<Framebuffer> Create(const FramebufferSpecs& spec);
	};
}