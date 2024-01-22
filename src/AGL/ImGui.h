#pragma once
#if defined __DEBUG__ || __RELEASE__
	#include<ImGui/imgui.h>
	#include<ImGui/imgui_impl_glfw.h>
	#include<ImGui/imgui_impl_opengl3.h>
	#define IMGUI_INIT	ImGui::CreateContext(); IMGUI_CHECKVERSION()
	#define IMGUI_IMPLGL(window)	ImGui_ImplGlfw_InitForOpenGL(window, true); ImGui_ImplOpenGL3_Init()
	#define IMGUI_TERMINATE	ImGui_ImplOpenGL3_Shutdown(); ImGui_ImplGlfw_Shutdown(); ImGui::DestroyContext()
	#define IMGUI_NEW_FRAME	ImGui_ImplOpenGL3_NewFrame(); ImGui_ImplGlfw_NewFrame(); ImGui::NewFrame()
	#define IMGUI_RENDER	ImGui::Render(); ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData())
	#define IMGUI_CALL(func) func
#else
	#define IMGUI_INIT	1
	#define IMGUI_IMPLGL(window)
	#define IMGUI_TERMINATE
	#define IMGUI_NEW_FRAME
	#define IMGUI_RENDER	
	#define IMGUI_CALL(func) 
#endif

