#include "rune_pch.h"

#include "RenderCommand.h"

#include "Rune/Renderer/Platform/OpenGL/OpenGLRendererAPI.h"

namespace Rune {
	
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}

