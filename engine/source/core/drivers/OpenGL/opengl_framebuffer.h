#pragma once
#include "core/servers/rendering/renderer/framebuffer.h"
#include "glad/glad.h"
namespace Forge {

	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecs& spec);
		virtual ~OpenGLFramebuffer();
		void Invalidate();
		virtual const FramebufferSpecs& GetFSpecs() const override { return m_Specification; }
		virtual const uint32_t GetColorAttachmentID() const override { return m_ColorAttachment; }  
		virtual void bind() const override;
		virtual void unbind()const override;
	private:
		FramebufferSpecs m_Specification;
		uint32_t m_ColorAttachment;
		uint32_t m_DepthAttachment;
		uint32_t m_RendererID;
	};
}
