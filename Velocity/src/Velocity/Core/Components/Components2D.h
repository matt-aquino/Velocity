#pragma once
#include "CoreComponents.h"

namespace Velocity
{
	// =============================================
	// ================ RENDERING ==================
	// =============================================

	struct SpriteComponent
	{
		// store textures in here
		SpriteComponent()
		{
		}

		// SpriteComponent(Texture texture) = default;

	};

	struct SpriteRendererComponent
	{
		// renders the sprites
		SpriteRendererComponent()
		{
		}
		

		void RenderSprite();
	};

	// =============================================
	// ================ COLLISION ==================
	// =============================================

	struct BoxCollider2DComponent : ColliderComponent
	{
		BoxCollider2DComponent()
		{
		}

		void UpdateTransform() override {}
		
	};

	struct CircleColliderComponent : ColliderComponent
	{
		CircleColliderComponent()
		{
		}

		void UpdateTransform() override {}

	};

	struct EdgeColliderComponent : ColliderComponent
	{
		EdgeColliderComponent()
		{
		}

		void UpdateTransform() override {}

	};

	// =============================================
	// ================ PHYSICS ====================
	// =============================================

	struct Rigidbody2DComponent
	{
		Rigidbody2DComponent()
		{
		}

	};
}