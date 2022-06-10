#include "vlpch.h"
#include "Velocity/Core/Application.h"
#include "EditorLayer.h"

#include "Velocity/Input/Input.h"
#include "Velocity/Input/KeyCodes.h"
#include "Velocity/Input/MouseButtonCodes.h"

#include "Velocity/Scene/GameObject.h"
#include "Velocity/Renderer/Mesh.h"
#include "Velocity/Core/Components/Components3D.h"
#include "Velocity/Renderer/RenderCommand.h"
#include "Velocity/Renderer/Renderer.h"

#include "ImGui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


namespace Velocity
{
	EditorLayer::EditorLayer() : m_EditorCamera(glm::vec3(0.0f, 0.0f, 5.0f))
	{
		lastMouseX = 0.0f;
		lastMouseY = 0.0f;

		
	}

	void EditorLayer::OnAttach()
	{
		Velocity::FramebufferSpecs fbSpecs;
		fbSpecs.Width = 1280;
		fbSpecs.Height = 720;
		m_Framebuffer = Velocity::Framebuffer::Create(fbSpecs);
		m_TextureShader = Velocity::Shader::Create("Assets/Shaders/texture.glsl");
		m_Texture = Velocity::Texture2D::Create("Assets/Textures/stonebrick.png");
		m_TextureShader->Bind();
		m_TextureShader->UploadUniformFloat("uTexture", 0);

		// set up scene objects
		m_Scene = new Scene();

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

		Velocity::GameObject* texturedCube = m_Scene->CreateGameObject("Textured Cube");

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
	}

	void EditorLayer::OnDetach()
	{
		delete m_Scene;
	}

	void EditorLayer::OnUpdate(float deltaTime)
	{
		// only update camera when holding RMB
		if (Input::IsMouseButtonPressed(VL_MOUSE_BUTTON_RIGHT))
		{
			auto [x, y] = Input::GetMousePosition();

			if (firstMouseMove)
			{
				lastMouseX = x;
				lastMouseY = y;
				firstMouseMove = false;
			}

			float xOffset = x - lastMouseX;
			float yOffset = y - lastMouseY;
			lastMouseX = x;
			lastMouseY = y;

			float sensitivity = 0.1f;
			xOffset *= sensitivity;
			yOffset *= sensitivity;

			m_EditorCamera.AddCameraPitch(yOffset);
			m_EditorCamera.AddCameraYaw(xOffset);


			// update camera movement
			if (Input::IsKeyPressed(VL_KEY_W))
				m_EditorCamera.MoveCamera(PerspectiveCamera::CameraDirection::FORWARD, deltaTime);

			else if (Input::IsKeyPressed(VL_KEY_S))
				m_EditorCamera.MoveCamera(PerspectiveCamera::CameraDirection::BACKWARD, deltaTime);

			if (Input::IsKeyPressed(VL_KEY_A))
				m_EditorCamera.MoveCamera(PerspectiveCamera::CameraDirection::LEFT, deltaTime);

			else if (Input::IsKeyPressed(VL_KEY_D))
				m_EditorCamera.MoveCamera(PerspectiveCamera::CameraDirection::RIGHT, deltaTime);

			if (Input::IsKeyPressed(VL_KEY_Q))
				m_EditorCamera.MoveCamera(PerspectiveCamera::CameraDirection::DOWN, deltaTime);

			else if (Input::IsKeyPressed(VL_KEY_E))
				m_EditorCamera.MoveCamera(PerspectiveCamera::CameraDirection::UP, deltaTime);

		}

		else
			firstMouseMove = true;

		// update scene
		m_Framebuffer->Bind();
		Velocity::RenderCommand::Clear();
		Velocity::Renderer::BeginScene(m_EditorCamera);
		m_Texture->Bind();
		Velocity::Renderer::Submit(m_Scene->GetRegistry(), m_TextureShader);
		Velocity::Renderer::EndScene();
		m_Framebuffer->Unbind();
	}

	void EditorLayer::OnImGuiRender(float deltaTime)
	{
		static bool dockSpaceOpen = true, opt_fullscreen_persistent = true;
		bool opt_fullscreen = opt_fullscreen_persistent;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// parent window turns docking off to avoid having two docking targets within each other
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// using this prevents Begin() from rendering a background
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("Editor Dockspace", &dockSpaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_ID = ImGui::GetID("MyDockspace");
			ImGui::DockSpace(dockspace_ID, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit")) Application::Get().Close();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		// Viewport window should be created first, then the renderer should create framebuffers
		// based on viewport size. then resize when viewport is changed.
		
		// editor windows
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
			ImGui::Begin("Viewport");
			{
				// resize framebuffers if needed before drawing 
				ImVec2 viewportSize = ImGui::GetContentRegionAvail();
				if (m_ViewportSize != *((glm::vec2*)&viewportSize))
				{
					m_ViewportSize = { viewportSize.x, viewportSize.y };
					m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
					m_EditorCamera.SetAspectRatio((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
				}
				uint32_t textureID = m_Framebuffer->GetColorAttachmentID();
				ImGui::Image((void*)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

			}
			ImGui::End();
			ImGui::PopStyleVar();

			ImGui::Begin("Hierarchy");
			{
				if (ImGui::TreeNode("Example Scene Object"))
				{
					ImGui::Text("Display object's children here");
					ImGui::TreePop();
				}
			}
			
			ImGui::End();

			// file management
			ImGui::Begin("Project");
			ImGui::End();

		}
		

		ImGui::End(); // end dockspace
	}

	void EditorLayer::OnEvent(Event& event)
	{
	}

	bool EditorLayer::OnMouseScroll(MouseScrollEvent& event)
	{
		float offset = event.GetYOffset();
		float fov = m_EditorCamera.GetFOV();
		fov += offset;
		m_EditorCamera.SetCameraFOV(fov);
		return true;
	}

	bool EditorLayer::OnWindowResize(WindowResizeEvent& event)
	{
		//uint32_t width = event.GetWidth(), height = event.GetHeight();
		//m_EditorCamera.SetAspectRatio(width, height);
		return false;
	}
}