#include <Evil.h>
#include <Evil/Core/EntryPoint.h>

#include "GameLayer.h"

class MiniGame : public Evil::Application
{
public:
	MiniGame()
	{
		PushLayer(new GameLayer());
	}
	~MiniGame()
	{

	}
};

Evil::Application* Evil::CreateApplication() 
{
	return new MiniGame();
}
