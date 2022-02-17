#pragma once
#include "Event.h"

namespace Velocity
{
	class VELOCITY_API MouseMovedEvent : public Event
	{
	public:

		MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}
		
		EVENT_CLASS_TYPE(MOUSE_MOVE)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)


	private:
		float m_MouseX, m_MouseY;
	};

	class VELOCITY_API MouseScrollEvent : public Event
	{
	public:
		MouseScrollEvent(float x, float y) : m_XOffset(x), m_YOffset(y) {}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrollEvent: " << m_XOffset<< ", " << m_YOffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MOUSE_SCROLL)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_XOffset, m_YOffset;
	};

	class VELOCITY_API MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:
		MouseButtonEvent(int button) : m_Button(button) {}

		int m_Button;
	};

	class VELOCITY_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MOUSE_PRESS)
	};

	class VELOCITY_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MOUSE_RELEASE)
	};
}