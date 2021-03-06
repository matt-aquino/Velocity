#pragma once
#include "Velocity/Core/Layers/Layer.h"
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

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}