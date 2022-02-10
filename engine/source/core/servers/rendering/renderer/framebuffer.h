#pragma once
#include "core/core.h"
namespace Forge {

	struct FramebufferSpecs
	{
		uint32_t width, height;
		bool SwapChainTarget = false;
	};

	class Framebuffer
	{
	public:
		virtual const FramebufferSpecs& GetFSpecs() const = 0;
		virtual const uint32_t GetColorAttachmentID() const = 0;

		virtual void bind() const = 0;
		virtual void unbind()const = 0;

		static FRef<Framebuffer>create(const FramebufferSpecs& spec);
	};
}