#include "rune_pch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace Rune {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle) {
		RUNE_PROFILE_FUNCTION();
		RUNE_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init() {
		RUNE_PROFILE_FUNCTION();
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		RUNE_CORE_ASSERT(status, "Failed to initialize Glad!");

		RUNE_CORE_INFO("OpenGL Info:");
		RUNE_CORE_INFO("  Vendor: {0}", (const char*) glGetString(GL_VENDOR));
		RUNE_CORE_INFO("  Renderer: {0}", (const char*) glGetString(GL_RENDERER));
		RUNE_CORE_INFO("  Version: {0}", (const char*) glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers() {
		RUNE_PROFILE_FUNCTION();
		glfwSwapBuffers(m_WindowHandle);
	}

}