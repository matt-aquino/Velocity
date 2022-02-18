#pragma once
#include "vlpch.h"

#include "Velocity/Core.h"
#include "Velocity/Events/Event.h"

namespace Velocity
{
	struct WindowProperties
	{
		std::string Title;
		unsigned int Width, Height;

		WindowProperties(const std::string& title = "Velocity", unsigned int width = 1280, unsigned int height = 720)
			: Title(title), Width(width), Height(height) {}
	};


	class VELOCITY_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProperties& props = WindowProperties());
	};
}