#include <Velocity.h>
#include "Velocity/Core/Core.h"
#include "Velocity/Scene/GameObject.h"
#include "Velocity/Scene/Scene.h"

#include "Velocity/Core/Components/CoreComponents.h"
#include "Velocity/Core/Components/Components3D.h"

#include "ImGui/imgui.h"
#include <cmath>
#include "glm/gtc/type_ptr.hpp"
#include <vector>
#include <array>

/*
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
		Velocity::Ref<Velocity::VertexBuffer> vertexBuffer;
		Velocity::Ref<Velocity::IndexBuffer> indexBuffer;

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
	Velocity::Ref<Velocity::Shader> m_Shader;
	Velocity::Ref<Velocity::VertexArray> m_VertexArray;

	// Camera
	Velocity::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 1.0f;
	float m_CameraRotationSpeed = 180.0f;
};

*/
class PerspectiveLayer : public Velocity::Layer
{
public:
	PerspectiveLayer() : Layer("Perspective"), m_Camera(glm::vec3(0.0f, 0.0f, 5.0f))
	{
		m_Scene = std::make_unique<Velocity::Scene>();

		m_CameraPosition = m_Camera.GetPosition();

		Velocity::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });

		// flat color shapes
		/*
		{
			float flatColorCubeVertices[3 * 8] = // 8 vertices in a cube, 3 floats each vertex position
			{
				-0.5f, 0.5f, 0.5f,	 
				-0.5f, -0.5f, 0.5f, 
				0.5f, -0.5f, 0.5f,	 
				0.5f, 0.5f, 0.5f,	 
			
				0.5f, 0.5f, -0.5f,	 
				0.5f, -0.5f, -0.5f,	 
				-0.5f, -0.5f, -0.5f,	 
				-0.5f, 0.5f, -0.5f	 
			};

			// 12 triangles, 3 verts each
			uint32_t cubeIndices[3 * 12] = 
			{
				0, 1, 2, // front
				0, 2, 3,
				3, 2, 5, // right
				3, 5, 4,
				4, 5, 6, // back
				4, 6, 7,
				7, 6, 1, // left
				7, 1, 0,
				7, 0, 3, // top
				7, 3, 4,
				1, 6, 5, // bottom
				1, 5, 2
			};
		
			float planeVertices [3 * 4] =
			{
				1.5f,  0.5f, 0.0f,
				1.5f, -0.5f, 0.0f,
				2.5f, -0.5f, 0.0f,
				2.5f,  0.5f, 0.0f
			};

			uint32_t planeIndices [3 * 2] =
			{
				0, 1, 2,
				0, 2, 3
			};

			Velocity::GameObject* flatColorCube = m_Scene->CreateGameObject(std::string("Flat Color Cube"));
			Velocity::Mesh flatColorCubeMesh(flatColorCubeVertices, 24, cubeIndices, 36);
			flatColorCube->AddComponent<Velocity::MeshComponent>(flatColorCubeMesh);

			Velocity::GameObject* plane = m_Scene->CreateGameObject(std::string("Plane"));
			Velocity::Mesh planeMesh(planeVertices, 12, planeIndices, 6);
			plane->AddComponent<Velocity::MeshComponent>(planeMesh);

			// flat color shader
			std::string flatColorVertexSrc =
				R"(
				#version 460 core
				layout (location = 0) in vec3 aPos;

				layout (location = 0) out vec3 vPos;
				layout (location = 1) out vec4 vColor;

				uniform mat4 uViewProj;
				uniform mat4 uModelMat;

				void main()
				{
					vPos = aPos;
					vColor = vec4(vPos, 1.0f);
					gl_Position = uViewProj * uModelMat * vec4(vPos, 1.0f);
				}
				)";

			std::string flatColorFragSrc =
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

			m_FlatColorShader.reset(Velocity::Shader::Create(flatColorVertexSrc, flatColorFragSrc));
		}
		
		*/

		// some coords need to be duplicated because of differing texture coords
		float texturedCubeVertices[5 * 24] = 
		{
		//  [	  position	   ] [tex coord]
			-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, // 0  // front face
			-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // 1  
			 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, // 2  
			 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, // 3  

			 0.5f,  0.5f, -0.5f, 0.0f, 1.0f, // 4  // back face
			 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // 5  
			-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // 6  
			-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, // 7  

			-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, // 8  // left face
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // 9
			-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, // 10
			-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, // 11

			 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, // 12  // right face
			 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // 13
			 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // 14
			 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, // 15

			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // 16  // top face
			-0.5f, 0.5f,  0.5f, 0.0f, 0.0f, // 17
			 0.5f, 0.5f,  0.5f, 1.0f, 0.0f, // 18
			 0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // 19

			-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, // 20  // bottom face
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // 21
			 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // 22
			 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, // 23
		};

		uint32_t texturedCubeIndices[3 * 12] =
		{
			0, 1, 2, // front
			0, 2, 3,
			4, 5, 6, // back
			4, 6, 7,
			8, 9, 10, // left
			8, 10, 11,
			12, 13, 14, // right
			12, 14, 15,
			16, 17, 18, // top
			16, 18, 19,
			20, 21, 22, // bottom
			20, 22, 23,
		};

		Velocity::GameObject* texturedCube = m_Scene->CreateGameObject(std::string("Textured Cube"));

		Velocity::Ref<Velocity::VertexBuffer> textureVB;
		Velocity::Ref<Velocity::IndexBuffer> textureIB;

		Velocity::BufferLayout textureLayout = {
			{Velocity::ShaderDataType::Float3, "aPos", false},
			{Velocity::ShaderDataType::Float2, "aTexCoord", false},
		};

		textureVB.reset(Velocity::VertexBuffer::Create(texturedCubeVertices, 5 * 24 * sizeof(float)));
		textureVB->SetLayout(textureLayout);

		textureIB.reset(Velocity::IndexBuffer::Create(texturedCubeIndices, 3 * 12 * sizeof(uint32_t)));

		Velocity::Mesh texturedCubeMesh(textureVB, textureIB);
		texturedCube->AddComponent<Velocity::MeshComponent>(texturedCubeMesh);

		// texture shader
		{
			std::string textureVertexSrc =
				R"(
				#version 460 core
				layout (location = 0) in vec3 aPos;
				layout (location = 1) in vec2 aTexCoord;

				layout (location = 0) out vec3 vPos;
				layout (location = 1) out vec2 vTexCoord;

				uniform mat4 uViewProj;
				uniform mat4 uModelMat;

				void main()
				{
					vPos = aPos;
					vTexCoord = aTexCoord;
					gl_Position = uViewProj * uModelMat * vec4(vPos, 1.0f);
				}
				)";

			std::string textureFragSrc =
				R"(
				#version 460 core
				layout (location = 0) in vec3 vPos;
				layout (location = 1) in vec2 vTexCoord;
				layout (location = 0) out vec4 fragColor;

				uniform sampler2D uTexture;

				void main()
				{
					fragColor = texture(uTexture, vTexCoord);
				}
				)";

			m_TextureShader.reset(Velocity::Shader::Create(textureVertexSrc, textureFragSrc));
			m_Texture = Velocity::Texture2D::Create("Assets/Textures/stonebrick.png");

			m_TextureShader->Bind();
			m_TextureShader->UploadUniformInt("uTexture", 0);
		}
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
		
		if (Velocity::Input::IsMouseButtonPressed(VL_MOUSE_BUTTON_RIGHT))
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

		//Velocity::Renderer::Submit(m_Scene->GetRegistry(), m_FlatColorShader);
		m_Texture->Bind();
		Velocity::Renderer::Submit(m_Scene->GetRegistry(), m_TextureShader);

		Velocity::Renderer::EndScene();
	}

	virtual void OnImGuiRender(float deltaTime) override
	{
		ImGui::Begin("Perspective Camera");
		{
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

			float fov = m_Camera.GetFOV();
			ImGui::Text("Camera FOV");
			ImGui::SameLine();
			ImGui::Text(std::to_string(m_Camera.GetFOV()).c_str(), "%.2f");
		}
		ImGui::End();
	}

	void OnEvent(Velocity::Event& event) override
	{
		Velocity::EventDispatcher d(event);
		d.Dispatch<Velocity::MouseScrollEvent>(VL_BIND_EVENT_FN(PerspectiveLayer::OnMouseScroll));
	}

	bool OnMouseScroll(Velocity::MouseScrollEvent& event)
	{
		float offset = event.GetYOffset();
		float fov = m_Camera.GetFOV();
		fov += offset * 0.1f; // scale down the zoom
		m_Camera.SetCameraFOV(fov);
		return true;
	}

	private:
		Velocity::Ref<Velocity::Shader> m_FlatColorShader, m_TextureShader;
		Velocity::Ref<Velocity::Texture2D> m_Texture;
		
		Velocity::Scope<Velocity::Scene> m_Scene;

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