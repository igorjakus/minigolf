#include"dtl.h"
#include"pch.h"
#include<Window.h>
#include"Shader.h"
#include"Agl.h"

int main() 
{
	agl::Init();
	agl::Window win1(640, 480, "minigolf");

	win1.create();
	win1.setIcon("assets/icon/icon.png", "assets/icon/icon.png");
	win1.setWindowPos(640, 300);

	while (!win1.closeCallBack())
	{
	


		win1.FEP();
	}
	
	return 0;
}
