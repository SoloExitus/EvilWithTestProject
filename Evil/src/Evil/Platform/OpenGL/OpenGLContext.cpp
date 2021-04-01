#include "evilpch.h"
#include "Evil/Platform/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Evil
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		EVIL_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		EVIL_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		EVIL_CORE_ASSERT(status, "Failed to initialize Glad!");

		EVIL_CORE_INFO("OpenGL info:");
		EVIL_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		EVIL_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		EVIL_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

		EVIL_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Evil requires at least OpenGL version 4.5!");
	}

	void OpenGLContext::SwapBuffers()
	{
		EVIL_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}
}
