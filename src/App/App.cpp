#include"dtl.h"
#include"pch.h"
#include<Window.h>
#include"Shader.h"
#include"Agl.h"

int main() 
{
	agl::Init();
	agl::Window win1(640, 480, "minigolf");

	win1.Create();
	win1.SetIcon("assets/icon/icon.png", "assets/icon/icon.png");
	win1.SetWindowPos(640, 300);
	

	while (win1.CloseCallBack())
	{
	



		win1.FEP();
	}
	
	return 0;
}
