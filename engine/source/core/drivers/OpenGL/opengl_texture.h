#pragma once
#include "core/servers/rendering/renderer/texture.h"
namespace Forge {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const FString& path);
		virtual ~OpenGLTexture2D();
		virtual uint32_t GetTexWidth() const override { return m_TexWidth; }
		virtual uint32_t GetTexHeight() const override { return m_TexHeight; }
		virtual void bind(uint32_t slot) const override;
	private:
		FString m_Path;
		uint32_t m_TexWidth;
		uint32_t m_TexHeight;
		uint32_t m_RendererID;
	};


}