#pragma once

namespace Velocity
{
	enum class RendererAPI
	{
		NONE = 0,
		OPENGL = 1,  // Most platforms
		DIRECTX = 2, // Windows exclusive
		VULKAN = 3,  // every platform
		METAL = 4,   // Apple exclusive
		GLES = 5	 // mobile devices and older hardware
	};


	class Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return s_RendererAPI; }

	private:
		static RendererAPI s_RendererAPI;
	};
}