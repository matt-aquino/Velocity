#pragma once
#include "Velocity/Renderer/Texture.h"

namespace Velocity
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }

		virtual void Bind(uint32_t slot = 0) const override;

	private:
		uint32_t m_Width, m_Height, m_RendererID;
	};


	class OpenGLTexture3D : public Texture3D
	{
	public:
		OpenGLTexture3D(const std::string& path);
		virtual ~OpenGLTexture3D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }
		uint32_t GetDepth() const { return m_Depth; }

		virtual void Bind(uint32_t slot = 0) const override;

	private:
		uint32_t m_Width, m_Height, m_Depth, m_RendererID;
	};

	class OpenGLCubemap : public Cubemap
	{
	public:
		OpenGLCubemap(const std::string& path);
		virtual ~OpenGLCubemap();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }
		uint32_t GetDepth() const { return m_Depth; }

		virtual void Bind(uint32_t slot = 0) const override;
	private:
		uint32_t m_Width, m_Height, m_Depth, m_RendererID;
	};
}