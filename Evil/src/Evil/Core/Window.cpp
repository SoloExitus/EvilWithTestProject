#include "evilpch.h"
#include "Evil/Core/Window.h"

#ifdef EVIL_PLATFORM_WINDOWS
	#include "Evil/Platform/Windows/WindowsWindow.h"
#endif

namespace Evil
{

	Scope<Window> Window::Create(const WindowProps& props)
	{
		#ifdef EVIL_PLATFORM_WINDOWS
			return CreateScope<WindowsWindow>(props);
		#else
			EVIL_CORE_ASSERT(false, "Unknown platform!");
			return nullptr;
		#endif
	}

}