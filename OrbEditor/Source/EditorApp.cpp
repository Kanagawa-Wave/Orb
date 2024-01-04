#include "pch.h"

#include <Core/EntryPoint.h>

namespace Orb
{
	class EditorApp : public Application
	{
	public:
		EditorApp() : Application({ "Editor", 800, 600 })
		{
		}
	};

	Application* CreateApplication()
	{
		return new EditorApp();
	}
}
