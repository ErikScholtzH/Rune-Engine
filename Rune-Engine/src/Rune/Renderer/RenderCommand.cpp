#include "rune_pch.h"

#include "RenderCommand.h"

#include "Rune/Renderer/Platform/OpenGL/OpenGLRendererAPI.h"

namespace Rune {
	
	Scope<RendererAPI> RenderCommand::s_RendererAPI = CreateScope<OpenGLRendererAPI>() ;

}

