#include "Engine.h"

Engine::Engine()
{
	Renderer renderer;
	this->renderer = renderer;
}

void Engine::Execute()
{
	renderer.Execute();
}
