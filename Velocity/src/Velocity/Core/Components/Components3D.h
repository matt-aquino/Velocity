#pragma once
#include "CoreComponents.h"
#include "Velocity/Renderer/Mesh.h"

namespace Velocity
{
	// =============================================
	// ================ RENDERING ==================
	// =============================================

	struct MeshComponent
	{
		MeshComponent() = default;
		MeshComponent(Mesh& mesh) : m_Mesh(mesh) {}

		void SetMesh(Mesh& mesh) { m_Mesh = mesh; }

		Mesh m_Mesh;
	};

	struct MeshRendererComponent
	{
		// when attached, make sure object gets a default mesh component added

		MeshComponent* m_MeshComponent;
	};

	// =============================================
	// ================ COLLISION ==================
	// =============================================

	struct BoxColliderComponent
	{

	};

	struct SphereColliderComponent
	{

	};

	struct MeshColliderComponent
	{

	};

	struct CapsuleColliderComponent
	{

	};

	// =============================================
	// ================ PHYSICS ====================
	// =============================================

	struct RigidbodyComponent
	{

	};
}