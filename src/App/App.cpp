#include"dtl.h"
#include"pch.h"
#include<Window.h>
#include<Shader.h>
#include"Agl.h"


int main() 
{
#ifdef __DIST__
	dtl::Log.settings(DTL_DEFAULT, DTL_DEFAULT, DTL_DEFAULT, DTL_DEFAULT, DTL_PROGRAM_TIME, DTL_FILE);
	dtl::Log.setFile("Log_error.txt");
#endif

	agl::Init();
	agl::Window win1(640, 480, "minigolf");

	win1.create();
	win1.setIcon("assets/icon/icon.png", "assets/icon/icon.png");
	win1.setWindowPos(640, 300);


	while (!win1.closeCallBack())
	{
		win1.IsKeyPressed(12);

		win1.FEP();
	}
	
	return 0;
}
