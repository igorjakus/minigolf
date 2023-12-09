#include"pch.h"
#include"Window.h"
#include"Shader.h"
#include"Core.h"


int main() 
{
	agl::Init();
	GL::Window win1(640, 480, "test");

	win1.Create();
	GL::Shader("Shaders/DefaultShader.hlsl");

	while (win1.CloseCallBack())
	{





		win1.FEP();
	}
	
	return 0;
}
