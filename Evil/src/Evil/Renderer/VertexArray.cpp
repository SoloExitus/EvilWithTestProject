#include "evilpch.h"
#include "Evil/Renderer/VertexArray.h"

#include "Evil/Renderer/Renderer.h"
#include "Evil/Platform/OpenGL/OpenGLVertexArray.h"

namespace Evil
{
	Ref<VertexArray> VertexArray::Create()
	{

		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	EVIL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:	return CreateRef<OpenGLVertexArray>();


		}

		EVIL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}