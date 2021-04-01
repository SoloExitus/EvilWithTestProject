#include "evilpch.h"
#include "Evil/Renderer/Framebuffer.h"

#include "Evil/Renderer/Renderer.h"
#include "Evil/Platform/OpenGL/OpenGLframebuffer.h"

namespace Evil
{
	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		EVIL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:		return CreateRef<OpenGLFramebuffer>(spec);
		}

		EVIL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
