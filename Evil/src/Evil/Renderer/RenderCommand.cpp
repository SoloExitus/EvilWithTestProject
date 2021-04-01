#include "evilpch.h"
#include "Evil/Renderer/RenderCommand.h"

namespace Evil
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}