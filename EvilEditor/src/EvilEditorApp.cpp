#include <Evil.h>
#include <Evil/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Evil
{
	class EvilEditor : public Application
	{
	public:
		EvilEditor()
			: Application("Evil Editor")
		{
			PushLayer(new EditorLayer());
		}

		~EvilEditor()
		{

		}
	};

	Application* CreateApplication()
	{
		return new EvilEditor();
	}
}