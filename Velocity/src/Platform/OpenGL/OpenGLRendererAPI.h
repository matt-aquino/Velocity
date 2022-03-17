#pragma once
#include "Velocity/Renderer/RendererAPI.h"

namespace Velocity
{
	class OpenGLRendererAPI : public RendererAPI
	{
		virtual void Init() override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;
		virtual const char* GetGPU() override;
		virtual const char* GetAPIVersion() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		virtual std::pair<uint32_t, uint32_t> GetViewport() override;
	};
}