#include"dtl.h"
#include"pch.h"
#include<Window.h>
#include<Shader.h>
#include"Agl.h"
#include<ImGui/imgui.h>
#include<ImGui/imgui_impl_glfw.h>
#include<ImGui/imgui_impl_opengl3.h>

int main() 
{
#ifdef __DIST__
	dtl::Log.settings(DTL_DEFAULT, DTL_DEFAULT, DTL_DEFAULT, DTL_DEFAULT, DTL_PROGRAM_TIME, DTL_FILE);
	dtl::Log.setFile("Log_error.txt");
#endif

	agl::Init();
	/*temp*/
	ImGui::CreateContext();
	IMGUI_CHECKVERSION();
	/*/temp*/
	agl::Window win1(640, 480, "minigolf");


	win1.create();

	/*temp*/
	ImGui_ImplGlfw_InitForOpenGL(win1.passPointer(), true);
	ImGui_ImplOpenGL3_Init();
	/*/temp*/

	win1.setIcon("assets/icon/icon.png", "assets/icon/icon.png");
	win1.setWindowPos(640, 300);


	while (!win1.closeCallBack())
	{

		/*temp*/
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::ShowDemoWindow();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		/*/temp*/
		win1.FEP();
	}
	/*temp*/
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	/*/temp*/
	return 0;
}
