#include "evilpch.h"
#include "Evil/Renderer/GraphicsContext.h"

#include "Evil/Renderer/Renderer.h"
#include "Evil/Platform/OpenGL/OpenGLContext.h"

namespace Evil 
{
	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    EVIL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		EVIL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}