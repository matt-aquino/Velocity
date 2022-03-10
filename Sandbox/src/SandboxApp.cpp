#include <Velocity.h>
#include "ImGui/imgui.h"

class ExampleLayer : public Velocity::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
		Velocity::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });

		float verts[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f,	1.0f, 1.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,	1.0f, 1.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f,	1.0f, 1.0f, 1.0f, 1.0f
		};

		uint32_t indices[3] = { 0, 1, 2 };

		m_VertexArray.reset(Velocity::VertexArray::Create());
		m_VertexArray->Bind();

		// generate buffers
		std::shared_ptr<Velocity::VertexBuffer> vertexBuffer;
		std::shared_ptr<Velocity::IndexBuffer> indexBuffer;

		vertexBuffer.reset(Velocity::VertexBuffer::Create(verts, sizeof(verts)));

		Velocity::BufferLayout layout = {
			{Velocity::ShaderDataType::Float3, "aPos", false},
			{Velocity::ShaderDataType::Float4, "aColor", false}
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		indexBuffer.reset(Velocity::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
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

		std::string fragSrc =
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

		m_Shader.reset(new Velocity::Shader(vertexSrc, fragSrc));
	}

	void OnUpdate() override
	{
		Velocity::RenderCommand::Clear();

		Velocity::Renderer::BeginScene();
		Velocity::Renderer::Submit(m_VertexArray);
		Velocity::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{

	}

	void OnEvent(Velocity::Event& event) override
	{
	}

	bool OnKeyPressedEvent(Velocity::KeyPressedEvent& event)
	{
		if (event.GetKeyCode() == VL_KEY_ESCAPE)
		{

		}
		return false;
	}

private:
	std::shared_ptr<Velocity::Shader> m_Shader;
	std::shared_ptr<Velocity::VertexArray> m_VertexArray;
};

class Sandbox : public Velocity::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Velocity::Application* Velocity::CreateApplication()
{
	return new Sandbox();
}