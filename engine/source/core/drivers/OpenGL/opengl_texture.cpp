#include "frpch.h"
#include "opengl_texture.h"
#include "glad/glad.h"
#include "img_loader.h"
namespace Forge {


	OpenGLTexture2D::OpenGLTexture2D(const FString& path , const FString& flag)
		:m_Path(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		unsigned char* data = stbi_load(path.c_str(),&width,&height,&channels,0);
		if (data == NULL)
			FR_CORE_ERROR("Failed to load image'{0}'", data);
		m_TexWidth = width;
		m_TexHeight = height;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);

		if(flag=="")
			glTextureStorage2D(m_RendererID, 1, GL_RGB8, m_TexWidth, m_TexHeight);
		if (flag == "specular")
			glTextureStorage2D(m_RendererID, 1, GL_RED, m_TexWidth, m_TexHeight);
	
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		if(flag=="")
			glTextureSubImage2D(m_RendererID, 0, 0, 0, m_TexWidth, m_TexHeight, GL_RGBA, GL_UNSIGNED_BYTE, data);
		if(flag=="specular")
			glTextureSubImage2D(m_RendererID, 1, 0, 0, m_TexWidth, m_TexHeight, GL_RED, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::bind(uint32_t slot) const
	{
		
		glBindTextureUnit(slot, m_RendererID);
	}

}