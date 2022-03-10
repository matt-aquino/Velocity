#include "vlpch.h"
#include "Application.h"
#include "glad/glad.h"

#include "Input.h"
#include "Velocity/KeyCodes.h"

namespace Velocity
{
#define BIND_EVENT_FUNC(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		VL_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FUNC(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		float verts[3 * 3] =
		{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f,
		};

		uint32_t indices[3] = { 0, 1, 2 };
		
		// gen vertex data
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		m_VertexBuffer.reset(VertexBuffer::Create(verts, sizeof(verts)));

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)));

		std::string vertexSrc = 
			R"(
			#version 460 core
			layout (location = 0) in vec3 aPos;
			layout (location = 0) out vec3 vPos;
			void main()
			{
				vPos = aPos;
				gl_Position = vec4(vPos, 1.0f);
			}
			)";

		std::string fragSrc=
			R"(
			#version 460 core
			layout (location = 0) in vec3 vPos;
			layout (location = 0) out vec4 fragColor;

			void main()
			{
				fragColor = vec4(vPos * 0.5 + 0.5, 1.0f);
			}
			)";

		m_Shader.reset(new Shader(vertexSrc, fragSrc));
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClear(GL_COLOR_BUFFER_BIT);
			
			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			// update all our layers
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			if (Input::IsKeyPressed(VL_KEY_ESCAPE))
				m_Running = false;

			// begin rendering our ImGui overlay
			m_ImGuiLayer->Begin();

			// if any layers render to ImGui, render them
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();

			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void Application::OnEvent(Event & e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.m_Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}
}