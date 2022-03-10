#include "vlpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Velocity
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}