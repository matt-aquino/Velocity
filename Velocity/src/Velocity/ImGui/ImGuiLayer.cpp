#include "vlpch.h"
#include "ImGuiLayer.h"

#define IMGUI_IMPL_API 
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

#include <filesystem>

// temp
#include "Velocity/Core/Application.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Velocity
{
	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
		
	}

	void ImGuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		
		ImGui::StyleColorsDark();
		ImGuiStyle& style = ImGui::GetStyle();

		// Load Fonts
		io.Fonts->AddFontFromFileTTF("../Velocity/vendor/ImGui/misc/fonts/Cousine-Regular.ttf", 15.0f);
		io.Fonts->AddFontFromFileTTF("../Velocity/vendor/ImGui/misc/fonts/DroidSans.ttf", 15.0f);
		io.Fonts->AddFontFromFileTTF("../Velocity/vendor/ImGui/misc/fonts/ProggyClean.ttf", 15.0f);
		io.Fonts->AddFontFromFileTTF("../Velocity/vendor/ImGui/misc/fonts/ProggyTiny.ttf", 15.0f);
		io.Fonts->AddFontFromFileTTF("../Velocity/vendor/ImGui/misc/fonts/Roboto-Medium.ttf", 15.0f);

		ImFont* font = io.Fonts->AddFontFromFileTTF("../Velocity/vendor/ImGui/misc/fonts/Karla-Regular.ttf", 15.0f);
		IM_ASSERT(font != NULL);
		
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 460 core");
	}
	
	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Update and Render additional Platform Windows
		// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
		//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void ImGuiLayer::OnImGuiRender(float deltaTime)
	{
		static bool show = true;
		static std::string gpu = (char*)glGetString(GL_RENDERER);
		static std::string version = (char*)glGetString(GL_VERSION);

		// change fonts
		//ImGuiIO& io = ImGui::GetIO(); (void)io;
		//ImFont& font = io.Fonts;

		// render graphics information
		ImGui::Begin("Renderer");

		ImGui::Text("GPU: ");
		ImGui::SameLine(0.0f, 1.0f);
		ImGui::Text(gpu.c_str());

		ImGui::NewLine();
		ImGui::Text("OpenGL Version: ");
		ImGui::SameLine(0.0f, 1.0f);
		ImGui::Text(version.c_str());

		ImGui::End();

		if (show)
			ImGui::ShowDemoWindow(&show);
	}

}