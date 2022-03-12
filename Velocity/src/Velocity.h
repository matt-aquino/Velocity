#pragma once

// FOR USE BY VELOCITY APPLICATIONS

#include "Velocity/Application.h"
#include "Velocity/Core/Layers/Layer.h"
#include "Velocity/Core/Logging/Log.h"
#include "Velocity/Core/Components/CoreComponents.h"
#include "entt.hpp"

// ImGui
#include "Velocity/ImGui/ImGuiLayer.h"

// Input
#include "Velocity/Input/Input.h"
#include "Velocity/Input/KeyCodes.h"
#include "Velocity/Input/MouseButtonCodes.h"

// Events
#include "Velocity/Events/Event.h"

// Rendering
#include "Velocity/Renderer/Renderer.h"
#include "Velocity/Renderer/RenderCommand.h"
#include "Velocity/Renderer/Buffer.h"
#include "Velocity/Renderer/VertexArray.h"
#include "Platform/OpenGL/Shaders/Shader.h"
#include "Velocity/Renderer/Camera.h"

// ENTRY POINT
#include "Velocity/Core/EntryPoint.h"