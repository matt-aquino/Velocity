#include <Velocity.h>
#include "Velocity/Core.h"

#include "ImGui/imgui.h"
#include <cmath>

class ExampleLayer : public Velocity::Layer
{
public:
	ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f) // keep our 16:9 aspect ratio
	{
		m_CameraPosition = glm::vec3(0.0f);

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
			
			uniform mat4 uViewProj;
			
			void main()
			{
				vPos = aPos;
				vColor = aColor;
				gl_Position = uViewProj * vec4(vPos, 1.0f);
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

	void OnUpdate(float deltaTime) override
	{
		// update camera first
		if (Velocity::Input::IsKeyPressed(VL_KEY_UP) || Velocity::Input::IsKeyPressed(VL_KEY_W))
			m_CameraPosition.y += m_CameraMoveSpeed * deltaTime;

		else if (Velocity::Input::IsKeyPressed(VL_KEY_DOWN) || Velocity::Input::IsKeyPressed(VL_KEY_S))
			m_CameraPosition.y -= m_CameraMoveSpeed * deltaTime;

		if (Velocity::Input::IsKeyPressed(VL_KEY_LEFT) || Velocity::Input::IsKeyPressed(VL_KEY_A))
			m_CameraPosition.x -= m_CameraMoveSpeed * deltaTime;

		else if (Velocity::Input::IsKeyPressed(VL_KEY_RIGHT) || Velocity::Input::IsKeyPressed(VL_KEY_D))
			m_CameraPosition.x += m_CameraMoveSpeed * deltaTime;

		m_Camera.SetPosition(m_CameraPosition);

		Velocity::RenderCommand::Clear();

		Velocity::Renderer::BeginScene(m_Camera);

		Velocity::Renderer::Submit(m_VertexArray, m_Shader);

		Velocity::Renderer::EndScene();
	}

	virtual void OnImGuiRender(float deltaTime) override
	{
		ImGui::Begin("Example Layer");

		ImGui::SliderFloat("Camera Speed", &m_CameraMoveSpeed, 0.1f, 4.0f);

		ImGui::End();
	}

	void OnEvent(Velocity::Event& event) override
	{
	}

private:
	std::shared_ptr<Velocity::Shader> m_Shader;
	std::shared_ptr<Velocity::VertexArray> m_VertexArray;

	// Camera
	Velocity::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 1.0f;
	float m_CameraRotationSpeed = 180.0f;

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