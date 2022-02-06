#include "frpch.h"
#include "texture.h"
#include "core/servers/rendering/renderer/renderer_rd.h"
#include "core/drivers/OpenGL/opengl_texture.h"
namespace Forge {

	FRef<Texture2D> Texture2D::create(const FString& path)
	{
		switch (renderer::get_api())
		{
		case renderer_api::api::None: return nullptr;
		case renderer_api::api::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
		}
		return 0;
	}

}