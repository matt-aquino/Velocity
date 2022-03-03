#pragma once
#include "Velocity/Layer.h"
#include "Velocity/Events/MouseEvent.h"
#include "Velocity/Events/KeyEvent.h"
#include "Velocity/Events/AppEvent.h"

namespace Velocity
{
	class VELOCITY_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);

	private:

		// mouse events
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrollEvent& e);

		// key events
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);

		// app events
		bool OnWindowResizedEvent(WindowResizeEvent& e);

		float m_Time = 0.0f;
	};
}