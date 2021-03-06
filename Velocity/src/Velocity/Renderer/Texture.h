#pragma once

#include <string>
#include "Velocity/Core/Core.h"

namespace Velocity
{
	class Texture
	{
	public:
		virtual ~Texture() {}

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(const std::string& path);
	};

	class Texture3D : public Texture
	{
	public:
		static Ref<Texture3D> Create(const std::string& path);
	};

	class Cubemap : public Texture
	{
	public:
		static Ref<Cubemap> Create(const std::string& path);

	};
}