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

		float verts[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f,	1.0f, 1.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,	1.0f, 1.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f,	1.0f, 1.0f, 1.0f, 1.0f
		};

		uint32_t indices[3] = { 0, 1, 2 };
		
		m_VertexArray.reset(VertexArray::Create());
		m_VertexArray->Bind();

		// generate buffers
		std::shared_ptr<VertexBuffer> vertexBuffer;
		std::shared_ptr<IndexBuffer> indexBuffer;

		vertexBuffer.reset(VertexBuffer::Create(verts, sizeof(verts)));

		BufferLayout layout = {
			{ShaderDataType::Float3, "aPos", false},
			{ShaderDataType::Float4, "aColor", false}
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_VertexArray->Unbind();

		std::string vertexSrc = 
			R"(
			#version 460 core
			layout (location = 0) in vec3 aPos;
			layout (location = 1) in vec4 aColor;
			
			layout (location = 0) out vec3 vPos;
			layout (location = 1) out vec4 vColor;
			
			void main()
			{
				vPos = aPos;
				vColor = aColor;
				gl_Position = vec4(vPos, 1.0f);
			}
			)";

		std::string fragSrc=
			R"(
			#version 460 core
			layout (location = 0) in vec3 vPos;
			layout (location = 1) in vec4 vColor;
			layout (location = 0) out vec4 fragColor;

			void main()
			{
				fragColor = vColor;
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
			m_VertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
			m_VertexArray->Unbind();

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