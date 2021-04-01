#include "evilpch.h"
#include "Evil/Renderer/RendererAPI.h"

#include "Evil/Platform/OpenGL/OpenGLRendererAPI.h"

namespace Evil
{
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
			case RendererAPI::API::None:    EVIL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateScope<OpenGLRendererAPI>();
		}

		EVIL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}