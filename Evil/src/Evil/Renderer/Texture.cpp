#include "evilpch.h"
#include "Evil/Renderer/Texture.h"

#include "Evil/Renderer/Renderer.h"
#include "Evil/Platform/OpenGL/OpenGLTexture.h"

namespace Evil
{
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		EVIL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:		return CreateRef<OpenGLTexture2D>(width,height);
		}

		EVIL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		EVIL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:		return CreateRef<OpenGLTexture2D>(path);
		}
		
		EVIL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}