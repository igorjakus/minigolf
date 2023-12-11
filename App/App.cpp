#include"pch.h"
#include<Window.h>
#include"Shader.h"
#include"Core.h"

int main() 
{
	agl::Init();
	agl::Window win1(640, 480, "minigolf");
	win1.Create();
	win1.SetIcon("../../../icone/icone.png", "../../../icone/icone.png");
	win1.SetWindowPos(640, 300);
	

	while (win1.CloseCallBack())
	{
	



		win1.FEP();
	}
	
	return 0;
}
