#include "Velocity.h"
#include "Velocity/Core/EntryPoint.h"

#include "EditorLayer.h"

namespace Velocity
{
	class Editor : public Application
	{
	public:
		Editor()
		{
			PushLayer(new EditorLayer());
		}

		~Editor()
		{

		}

	};


	Application* CreateApplication()
	{
		return new Editor();
	}
}