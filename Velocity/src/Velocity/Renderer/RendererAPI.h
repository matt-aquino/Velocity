#pragma once
#include "glm/glm.hpp"
#include "VertexArray.h"

namespace Velocity
{
	class RendererAPI
	{
	public:
		enum class API
		{
			NONE = 0,
			OPENGL = 1,  // Most platforms
			DIRECTX = 2, // Windows exclusive
			VULKAN = 3,  // every platform
			METAL = 4,   // Apple exclusive
			GLES = 5	 // mobile devices and older hardware
		};

		virtual void Init() = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return s_API; }

	private:
		static API s_API;
	};
}