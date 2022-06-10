#pragma once
#include "Velocity/Core/Layers/Layer.h"
#include "Velocity/Renderer/Camera.h"
#include "Velocity/Renderer/Framebuffer.h"
#include "Velocity/Renderer/Shader.h"
#include "Velocity/Renderer/Texture.h"
#include "Velocity/Scene/Scene.h"

namespace Velocity
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(float deltaTime) override;
		virtual void OnImGuiRender(float deltaTime) override;

		virtual void OnEvent(Event& event) override;

		bool OnMouseScroll(MouseScrollEvent& event);
		bool OnWindowResize(WindowResizeEvent& event);

	private:
		PerspectiveCamera m_EditorCamera;

		// temp
		Ref<Framebuffer> m_Framebuffer;
		glm::vec2 m_ViewportSize;

		Ref<Shader> m_TextureShader;
		Ref<Texture2D> m_Texture;
		Scene* m_Scene;

		bool firstMouseMove = true;
		float lastMouseX, lastMouseY;
	};
}
