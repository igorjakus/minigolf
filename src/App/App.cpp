#include "dtl.h"
#include"pch.h"
#include"Window.h"
#include"Shader.h"
#include"Core.h"

int main() 
{
	agl::Init();
	GL::Window win1(640, 480, "test");

	int test;
	test++;
	DTL_INF("%d", test);

	win1.Create();
	while (win1.CloseCallBack())
	{





		win1.FEP();
	}
	
	return 0;
}
