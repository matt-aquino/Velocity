#include <Velocity.h>
#include "Velocity/Core/Core.h"
#include "Velocity/Core/Components/CoreComponents.h"

#include "ImGui/imgui.h"
#include <cmath>
#include "glm/gtc/type_ptr.hpp"

class OrthographicLayer : public Velocity::Layer
{
public:
	OrthographicLayer() : Layer("Orthographic"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f) // keep our 16:9 aspect ratio
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
		// update camera movement
		if (Velocity::Input::IsKeyPressed(VL_KEY_W))
			m_CameraPosition.y += m_CameraMoveSpeed * deltaTime;

		else if (Velocity::Input::IsKeyPressed(VL_KEY_S))
			m_CameraPosition.y -= m_CameraMoveSpeed * deltaTime;

		if (Velocity::Input::IsKeyPressed(VL_KEY_A))
			m_CameraPosition.x -= m_CameraMoveSpeed * deltaTime;

		else if (Velocity::Input::IsKeyPressed(VL_KEY_D))
			m_CameraPosition.x += m_CameraMoveSpeed * deltaTime;

		// Work on getting triangle drawn in perspective
		m_Camera.SetPosition(m_CameraPosition);

		Velocity::RenderCommand::Clear();

		Velocity::Renderer::BeginScene(m_Camera);

		Velocity::Renderer::Submit(m_VertexArray, m_Shader);

		Velocity::Renderer::EndScene();
	}

	virtual void OnImGuiRender(float deltaTime) override
	{
		ImGui::Begin("Orthographic Camera");

		ImGui::Text("Camera Position");
		ImGui::Text(std::to_string(m_Camera.GetPosition().x).c_str());
		ImGui::SameLine();
		ImGui::Text(std::to_string(m_Camera.GetPosition().y).c_str());
		
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


class PerspectiveLayer : public Velocity::Layer
{
public:
	PerspectiveLayer() : Layer("Perspective"), m_Camera(glm::vec3(0.0f, 0.0f, 5.0f))
	{
		m_CameraPosition = m_Camera.GetPosition();

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
		// update camera movement
		if (Velocity::Input::IsKeyPressed(VL_KEY_W))
			m_Camera.MoveCamera(Velocity::PerspectiveCamera::CameraDirection::FORWARD, deltaTime);
		
		else if (Velocity::Input::IsKeyPressed(VL_KEY_S))
			m_Camera.MoveCamera(Velocity::PerspectiveCamera::CameraDirection::BACKWARD, deltaTime);

		if (Velocity::Input::IsKeyPressed(VL_KEY_A))
			m_Camera.MoveCamera(Velocity::PerspectiveCamera::CameraDirection::LEFT, deltaTime);

		else if (Velocity::Input::IsKeyPressed(VL_KEY_D))
			m_Camera.MoveCamera(Velocity::PerspectiveCamera::CameraDirection::RIGHT, deltaTime);

		if (Velocity::Input::IsKeyPressed(VL_KEY_Q))
			m_Camera.MoveCamera(Velocity::PerspectiveCamera::CameraDirection::DOWN, deltaTime);

		else if (Velocity::Input::IsKeyPressed(VL_KEY_E))
			m_Camera.MoveCamera(Velocity::PerspectiveCamera::CameraDirection::UP, deltaTime);

		// update camera rotation
		
		if (Velocity::Input::IsMouseButtonPressed(VL_MOUSE_BUTTON_LEFT) || Velocity::Input::IsMouseButtonPressed(VL_MOUSE_BUTTON_RIGHT))
		{
			auto [x, y] = Velocity::Input::GetMousePosition();

			if (firstMouse)
			{
				lastMouseX = x;
				lastMouseY = y;
				firstMouse = false;
			}

			float xOffset = x - lastMouseX;
			float yOffset = y - lastMouseY;
			lastMouseX = x;
			lastMouseY = y;

			float sensitivity = 0.1f;
			xOffset *= sensitivity;
			yOffset *= sensitivity;

			m_Camera.AddCameraPitch(yOffset);
			m_Camera.AddCameraYaw(xOffset);
		}

		else
			firstMouse = true;


		Velocity::RenderCommand::Clear();

		Velocity::Renderer::BeginScene(m_Camera);

		Velocity::Renderer::Submit(m_VertexArray, m_Shader);

		Velocity::Renderer::EndScene();
	}

	virtual void OnImGuiRender(float deltaTime) override
	{
		ImGui::Begin("Perspective Camera");

		ImGui::Text("Camera Position");
		ImGui::Text(std::to_string(m_Camera.GetPosition().x).c_str());
		ImGui::SameLine();
		ImGui::Text(std::to_string(m_Camera.GetPosition().y).c_str());
		ImGui::SameLine();
		ImGui::Text(std::to_string(m_Camera.GetPosition().z).c_str());

		ImGui::Text("Camera Rotation");
		ImGui::Text("Pitch: ");
		ImGui::SameLine();
		ImGui::Text(std::to_string(m_Camera.GetPitch()).c_str(), "%.2f");
		ImGui::SameLine();
		ImGui::Text(" Yaw: ");
		ImGui::SameLine();
		ImGui::Text(std::to_string(m_Camera.GetYaw()).c_str(), "%.2f");

		float speed = m_Camera.GetCameraSpeed();
		ImGui::SliderFloat("Camera Speed", &speed, 0.1f, 4.0f);
		m_Camera.SetCameraSpeed(speed);

		ImGui::End();
	}

	void OnEvent(Velocity::Event& event) override
	{
	}

	private:
		std::shared_ptr<Velocity::Shader> m_Shader;
		std::shared_ptr<Velocity::VertexArray> m_VertexArray;

		Velocity::PerspectiveCamera m_Camera;
		glm::vec3 m_CameraPosition;
		float m_CameraMoveSpeed = 1.0f;
		float m_CameraRotationSpeed = 180.0f;
		bool firstMouse = true;
		float lastMouseX = 0.0f, lastMouseY = 0.0f;
};
class Sandbox : public Velocity::Application
{
public:
	Sandbox()
	{
		//PushLayer(new OrthographicLayer());
		PushLayer(new PerspectiveLayer());
	}

	~Sandbox()
	{

	}
};

Velocity::Application* Velocity::CreateApplication()
{
	return new Sandbox();
}