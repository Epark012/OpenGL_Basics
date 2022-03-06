#ifndef _Engine_H_Class_
#define _Engine_H_Class_

#include "Graphics/imgui/imgui.h"
#include "Graphics/imgui/imgui_impl_glfw.h"
#include "Graphics/imgui/imgui_impl_opengl3.h"


#include "Renderer.h"


class Engine 
{
public:
	Renderer renderer;
	
	Engine();

	void Execute();
};

#endif // !_Engine_H_Class_
